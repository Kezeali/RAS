/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../../include/Rocket/AngelScript/Core/ras_EventListenerInstancer.h"

#include <Rocket/Core/Log.h>
#include <Rocket/Core/Element.h>
#include <Rocket/Core/ElementDocument.h>

#include <sstream>


namespace Rocket { namespace AngelScript {

	//! Executes script code
	class InlineEventListener : public Rocket::Core::EventListener
	{
	public:
		InlineEventListener(asIScriptEngine *engine, const char * module, const Rocket::Core::String &script_string);
		virtual ~InlineEventListener();

		void ExceptionCallback(asIScriptContext *ctx);
		void LineCallback(asIScriptContext *ctx);

		void ProcessEvent(Core::Event& ev);

		void OnAttach(Rocket::Core::Element *element);
		void OnDetach(Rocket::Core::Element *element);

	private:
		asIScriptEngine *m_Engine;
		Rocket::Core::String m_ModuleName;
		Rocket::Core::String m_ScriptString;

		asIScriptModule *m_Module;
		asIScriptFunction *m_Func;

		Rocket::Core::Element *m_ParentElement;

		void acquireModule();
		int compile(const Rocket::Core::String &section_name);
	};

	InlineEventListener::InlineEventListener(asIScriptEngine *engine, const char * module, const Rocket::Core::String &script_string)
		: m_Engine(engine),
		m_ModuleName(module),
		m_ScriptString(script_string),
		m_Module(nullptr),
		m_Func(nullptr),
		m_ParentElement(nullptr)
	{
		acquireModule();
	}

	InlineEventListener::~InlineEventListener()
	{
		if (m_Func != nullptr)
			m_Func->Release();
	}

	void InlineEventListener::acquireModule()
	{
		if (m_Module == nullptr)
		{
			if (m_ModuleName != "this")
				m_Module = m_Engine->GetModule(m_ModuleName.CString(), asGM_CREATE_IF_NOT_EXISTS);
			else if (m_ParentElement != nullptr)
			{
				Rocket::Core::ElementDocument *doc = m_ParentElement->GetOwnerDocument();
				if (doc != nullptr)
					m_Module = m_Engine->GetModule(doc->GetSourceURL().CString());
			}
		}
	}

	int InlineEventListener::compile(const Rocket::Core::String &section_name)
	{
		int r = 0;
		if (m_Func == nullptr)
		{
			std::string funcCode = "void InlineEventFn(Event @event) {\n";
			funcCode += m_ScriptString.CString();
			funcCode += ";\n}"; // Semi-colon added in case event script doesn't have a final one (convinient for single statement scripts)

			r = m_Module->CompileFunction(section_name.CString(), funcCode.c_str(), -1, 0, &m_Func);
			ROCKET_ASSERTMSG(r >= 0, "Error while compiling inline-event function");
		}
		return r;
	}

	void InlineEventListener::ExceptionCallback(asIScriptContext *ctx)
	{
		asIScriptEngine *engine = ctx->GetEngine();

		std::ostringstream desc;
		desc << "Exception during inline-event: \n\t" << ctx->GetExceptionString() << std::endl;

		// Get exception info to dump
		int column = 0;
		int line = ctx->GetExceptionLineNumber(&column);

		int funcId = ctx->GetExceptionFunction();
		const asIScriptFunction *function = engine->GetFunctionById(funcId);

		if (function != nullptr)
		{
			desc << "  in function: " << function->GetDeclaration(false) << " (" << line << "," << column << ")" << std::endl;
			desc << "    in module: " << function->GetModuleName() << std::endl;
			desc << "   in section: " << function->GetScriptSectionName();
		}
		else
		{
			desc << "\t" << m_ScriptString.Substring(0, column).CString() << "<Error\n  " << m_ScriptString.Substring(column).CString();
		}

		Rocket::Core::Log::Message(Rocket::Core::Log::LT_ERROR, desc.str().c_str());
	}

	void InlineEventListener::LineCallback(asIScriptContext *ctx)
	{
		// Nothing yet (may add optional callback / signal to instancer ctor.)
	}

	void InlineEventListener::ProcessEvent(Core::Event& ev)
	{
		acquireModule();
		ROCKET_ASSERTMSG(m_Module != nullptr, ("Error executing inline-event function: the required script module (\"" + m_ModuleName + "\") doesn't exist").CString());
		if (m_Module == nullptr)
			return;
		int r;
		// Compile the event function if it hasn't been already (the method checks this)
		r = compile(ev.GetType());
		ROCKET_ASSERTMSG(r >= 0, "Failed to compile inline-event function");

		asIScriptContext *ctx = m_Engine->CreateContext();
		r = ctx->Prepare(m_Func->GetId());
		ROCKET_ASSERTMSG(r >= 0, "Failed to prepare inline-event function");
		if (r < 0)
		{
			m_Func->Release();
			m_Func = nullptr;
			ctx->Release();
			return;
		}

		ctx->SetExceptionCallback(asMETHOD(InlineEventListener, ExceptionCallback), this, asCALL_THISCALL);
		// I may add a line callback later (commented out for now):
		//ctx->SetLineCallback(asMETHOD(InlineEventListener, LineCallback), this, asCALL_THISCALL);

		// Need to manually add ref, since a ref will be dropped when the Event
		//  handle passed to the script fn. goes out of scope
		ev.AddReference();
		r = ctx->SetArgObject(0, &ev);

		r = ctx->Execute();
		ROCKET_ASSERTMSG(r >= 0, "Failed to execute inline-event function");
		ROCKET_ASSERTMSG(r == asEXECUTION_FINISHED, "Execution of inline-event function didn't complete");

		// Clear memory
		ctx->Release();
	}

	void InlineEventListener::OnAttach(Rocket::Core::Element *element)
	{
		if (m_ModuleName == "this")
			m_ParentElement = element;
	}

	void InlineEventListener::OnDetach(Rocket::Core::Element *element)
	{
		if (m_Func != nullptr)
		{
			m_Func->Release();
			m_Func = nullptr;
		}
	}

	// InlineEventListenerInstancer impl. follows
	InlineEventListenerInstancer::InlineEventListenerInstancer(asIScriptEngine *engine, const char *module)
		: m_Engine(engine),
		m_DefaultModule(module)
	{
	}

	InlineEventListenerInstancer::InlineEventListenerInstancer(asIScriptEngine *engine, const char *module,
		asSFuncPtr line_callback, void *line_callback_obj,
		asSFuncPtr exception_callback, void *exception_callback_obj)
		: m_Engine(engine),
		m_DefaultModule(module),
		m_LineCallback(line_callback, line_callback_obj),
		m_ExceptionCallback(exception_callback, exception_callback_obj)
	{}

	Core::EventListener * InlineEventListenerInstancer::InstanceEventListener(const Rocket::Core::String &value, Rocket::Core::Element* element)
	{
		// Check for non-default module specifier
		if (value[0] == '%')
		{
			Rocket::Core::String module;
			Rocket::Core::String::size_type end = value.Find(":", 1);
			if (end > 1 && end != Rocket::Core::String::npos)
				module = value.Substring(1, end-1);
			else
			{
				ROCKET_ERRORMSG(("The following inline event script has an invalid module directive: " + value).CString());
				end = 0;
			}

			return new InlineEventListener(m_Engine, module.CString(), value.CString() + end+1);
		}
		else
			return new InlineEventListener(m_Engine, m_DefaultModule, value.CString());
	}

	void InlineEventListenerInstancer::Release()
	{
		delete this;
	}

}}
