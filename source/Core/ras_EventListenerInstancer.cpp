/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../include/Rocket/AngelScript/Core/ras_EventListenerInstancer.h"

#include <Rocket/Core/Log.h>

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

	private:
		asIScriptEngine *m_Engine;
		EMP::Core::String m_Module;
		EMP::Core::String m_ScriptString;

		asIScriptContext *m_Ctx;
	};

	InlineEventListener::InlineEventListener(asIScriptEngine *engine, const char * module, const EMP::Core::String &script_string)
		: m_Engine(engine),
		m_Module(module),
		m_ScriptString(script_string)
	{
	}

	InlineEventListener::~InlineEventListener()
	{
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
		// String is compiled every time the event is fired, since the module might have been re-compiled in the interim
		//  (ExecuteString compiles the fn. with reguard to the module)
		int r = m_Engine->PrepareString(m_Module.CString(), "Event @ event", m_ScriptString.CString(), &m_Ctx/*, asEXECSTRING_USE_MY_CONTEXT*/);
		EMP_ASSERTMSG(r >= 0, "Error while compiling inline-event function");
		EMP_ASSERTMSG(r == asEXECUTION_PREPARED, "Failed to prepare inline-event function");
		if (r < 0) return;

		r = m_Ctx->SetArgAddress(0, &ev);
		// Need to manually add ref, since a ref will be dropped when the Event
		//  handle passed to the script fn. goes out of scope
		ev.AddReference();

		m_Ctx->SetExceptionCallback(asMETHOD(InlineEventListener, ExceptionCallback), this, asCALL_THISCALL);

		r = m_Ctx->Execute();
		EMP_ASSERTMSG(r >= 0, "Failed to execute inline-event function");
		EMP_ASSERTMSG(r == asEXECUTION_FINISHED, "Execution of inline-event function didn't complete");

		// Clear memory
		m_Ctx->Release();
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
