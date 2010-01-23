/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../include/Rocket/AngelScript/Core/ras_EventListenerInstancer.h"

#include <Rocket/Core/Log.h>
#include <Rocket/Core/Element.h>
#include <Rocket/Core/ElementDocument.h>

#include <sstream>


namespace Rocket { namespace AngelScript {

	//! Executes script code
	class InlineEventListener : public Rocket::Core::EventListener
	{
	public:
		InlineEventListener(asIScriptEngine *engine, const char * module, const EMP::Core::String &script_string);
		~InlineEventListener();

		void ExceptionCallback(asIScriptContext *ctx);

		void ProcessEvent(Core::Event& ev);

		void OnAttach(Rocket::Core::Element *element);

	private:
		asIScriptEngine *m_Engine;
		EMP::Core::String m_ModuleName;
		EMP::Core::String m_ScriptString;

		asIScriptModule *m_Module;
		asIScriptContext *m_Ctx;

		void acquireModule();
	};

	InlineEventListener::InlineEventListener(asIScriptEngine *engine, const char * module, const EMP::Core::String &script_string)
		: m_Engine(engine),
		m_ModuleName(module),
		m_ScriptString(script_string)
	{
		acquireModule();
	}

	InlineEventListener::~InlineEventListener()
	{
	}

	void InlineEventListener::acquireModule()
	{
		if (m_Module == NULL && m_ModuleName != "this")
			m_Module = m_Engine->GetModule(m_ModuleName.CString(), asGM_CREATE_IF_NOT_EXISTS);
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
		const asIScriptFunction *function = engine->GetFunctionDescriptorById(funcId);

		if (function != NULL)
		{
			desc << "  in function: " << function->GetDeclaration(false) << " (" << line << "," << column << ")" << std::endl;
			desc << "    in module: " << function->GetModuleName() << std::endl;
			desc << "   in section: " << function->GetScriptSectionName();
		}
		else
		{
			desc << "\t" << m_ScriptString.Substring(0, column).CString() << "<Error\n  " << m_ScriptString.Substring(column).CString();
		}

		Rocket::Core::Log::Message(EMP::Core::Log::LT_ERROR, desc.str().c_str());
	}

	void InlineEventListener::ProcessEvent(Core::Event& ev)
	{
		acquireModule();
		EMP_ASSERTMSG(m_Module != NULL, "Error while compiling inline-event function - required module doesn't exist");
		if (m_Module == NULL)
			return;

		std::string funcCode = "void InlineEventFn(Event @ event) {\n";
		funcCode += m_ScriptString.CString();
		funcCode += "\n;}";

		asIScriptFunction *func;
		int r = m_Module->CompileFunction(ev.GetType().CString(), funcCode.c_str(), -1, 0, &func);
		EMP_ASSERTMSG(r >= 0, "Error while compiling inline-event function");
		EMP_ASSERTMSG(r == asEXECUTION_PREPARED, "Failed to prepare inline-event function");
		if (r < 0) return;

		m_Ctx = m_Engine->CreateContext();
		r = m_Ctx->Prepare(func->GetId()); if (r < 0) { func->Release(); m_Ctx->Release(); }

		r = m_Ctx->SetArgAddress(0, &ev);
		// Need to manually add ref, since a ref will be dropped when the Event
		//  handle passed to the script fn. goes out of scope
		ev.AddReference();

		m_Ctx->SetExceptionCallback(asMETHOD(InlineEventListener, ExceptionCallback), this, asCALL_THISCALL);

		r = m_Ctx->Execute();
		EMP_ASSERTMSG(r >= 0, "Failed to execute inline-event function");
		EMP_ASSERTMSG(r == asEXECUTION_FINISHED, "Execution of inline-event function didn't complete");

		// Clear memory
		func->Release();
		m_Ctx->Release();
	}

	void InlineEventListener::OnAttach(Rocket::Core::Element *element)
	{
		if (m_ModuleName == "this")
		{
			Rocket::Core::ElementDocument *doc = element->GetOwnerDocument();
			if (doc != NULL)
				m_Module = m_Engine->GetModule(doc->GetSourceURL().CString());
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

	Core::EventListener * InlineEventListenerInstancer::InstanceEventListener(const EMP::Core::String &value)
	{
		// Check for non-default module specifier
		if (value[0] == '%')
		{
			EMP::Core::String module;
			EMP::Core::String::size_type end = value.Find(":", 1);
			if (end > 1 && end != EMP::Core::String::npos)
				module = value.Substring(1, end-1);
			else
			{
				EMP_ERRORMSG(("The following inline event script has an invalid module directive: " + value).CString());
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
