/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_EVENTLISTENER
#define H_ROCKET_AS_EVENTLISTENER

#include <Rocket/Core.h>
#include <angelscript.h>

#include <Inheritance/ScriptObjectWrapper.h>
#include <Calling/Caller.h>


namespace Rocket { namespace AngelScript {

	// The classes in this file are for EventListener classes / functions manually
	//  defined and registered in scripts.
	//  See ras_EventListenerInstancer.h for RML inline-event implementation / handling

	//! Base class for event listeners implemented in script
	class EventListenerWrapper : public Rocket::Core::EventListener, public ScriptUtils::Inheritance::ScriptObjectWrapper
	{
	public:
		ElementWrapper(asIScriptObject* self)
			: ScriptUtils::Inheritance::ScriptObjectWrapper(self, "IEventListener")
		{
		}

		virtual void ProcessEvent(Event& event)
		{
			ScriptUtils::Calling::Caller f = this->get_caller("void ProcessEvent(Event &inout)");
			if (f.ok())
				f(event);
		}
	};

	void RegisterEventListenerInterface(asIScriptEngine *engine)
	{
		int r = engine->RegisterInterface("IEventListener");
		EMP_ASSERT(r);
		r = engine->RegisterInterfaceMethod("IEventListener", "void ProcessEvent(Event &inout)");
		EMP_ASSERT(r);
	}


	//! Passes an event to a registered method
	class DelegatingEventListener : public Rocket::Core::EventListener
	{
	public:
		DelegatingEventListener(asIScriptEngine *engine, const std::string &callback_decl);

		virtual void ProcessEvent(Event& event);
	};

	DelegatingEventListener::DelegatingEventListener(asIScriptEngine *engine, const std::string &callback_decl)
	{
	}

	void DelegatingEventListener::ProcessEvent(Event &event)
	{
	}

}}

#endif