/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../../include/Rocket/AngelScript/Core/ras_ScriptedEventListener.h"

#include "../../include/Rocket/AngelScript/Core/ras_Exception.h"
#include "../../include/Rocket/AngelScript/Core/ras_EventConnection.h"

#include <Rocket/Core.h>

#include <ScriptUtils/Inheritance/ScriptObjectWrapper.h>
#include <ScriptUtils/Calling/Caller.h>


namespace Rocket { namespace AngelScript {

	//! Base class for event listeners implemented in script
	class EventListenerWrapper : public Rocket::Core::EventListener, public ScriptUtils::Inheritance::ScriptObjectWrapper
	{
	public:
		EventListenerWrapper(asIScriptObject* self)
			: ScriptUtils::Inheritance::ScriptObjectWrapper(self, "IEventListener")
		{
			_obj->Release();
		}

		virtual void ProcessEvent(Rocket::Core::Event& event)
		{
			ScriptUtils::Calling::Caller f = this->get_caller("void ProcessEvent(Event@)");
			if (f)
			{
				event.AddReference();
				f(&event);
			}
		}

		virtual void OnAttach(Rocket::Core::Element *element)
		{
			//ScriptUtils::Calling::Caller f = this->get_caller("void OnAttach(Element@)");
			//if (f)
			//{
			//	//element->AddReference();
			//	f(element);
			//}
		}

		virtual void OnDetach(Rocket::Core::Element *element)
		{
			//ScriptUtils::Calling::Caller f = this->get_caller("void OnDetach(Element@)");
			//if (f)
			//{
			//	//element->AddReference();
			//	f(element);
			//}
			delete this;
		}
	};

	void RegisterEventListenerInterface(asIScriptEngine *engine)
	{
		int r = engine->RegisterInterface("IEventListener");
		if (r < 0)
			throw Exception("Couldn't register IEventListener");
		r = engine->RegisterInterfaceMethod("IEventListener", "void ProcessEvent(Event@)");
		if (r < 0)
			throw Exception("Couldn't register IEventListener");

		// These are optional in the C++ EventListener interface, but we
		//  register them here anyway since an EventListener base class can be
		//  defined in script if the user so desires.
		r = engine->RegisterInterfaceMethod("IEventListener", "void OnAttach(Element@)");
		if (r < 0)
			throw Exception("Couldn't register IEventListener");
		r = engine->RegisterInterfaceMethod("IEventListener", "void OnDetach(Element@)");
		if (r < 0)
			throw Exception("Couldn't register IEventListener");
	}

	typedef std::tr1::unordered_map<asIScriptObject*, EventListenerWrapper*> ListenerRegistry;
	static ListenerRegistry listenerRegistry;

	template <class T>
	EventConnection *AddScriptedEventListener(const Rocket::Core::String &event_type, asIScriptObject *listener, bool in_capture_phase, T *obj)
	{
		if (listener != NULL)
		{
			EventListenerWrapper *listenerWrapper = new EventListenerWrapper(listener);
			obj->AddEventListener(event_type, listenerWrapper, in_capture_phase);

			//listenerRegistry[listener] = listenerWrapper;
			listener->Release();

			return new EventConnectionTemplate<T>(obj, event_type, listenerWrapper, in_capture_phase);
		}
		else
			return NULL;
	}

	template <class T>
	EventConnection *AddScriptedEventListener(const Rocket::Core::String &event_type, asIScriptObject *listener, T *obj)
	{
		return AddScriptedEventListener(event_type, listener, false, obj);
	}

	template <class T>
	void RemoveScriptedEventListener(const Rocket::Core::String &event, asIScriptObject *listener, T *obj)
	{
		if (listener != NULL)
		{
			ListenerRegistry::iterator _where = listenerRegistry.find(listener);
			if (_where != listenerRegistry.end())
			{
				EventListenerWrapper *listenerWrapper = _where->second;
				obj->RemoveEventListener(event, listenerWrapper);

				listenerRegistry.erase(_where);
				//delete listenerWrapper;

				listener->Release();
			}
		}
	}

	template <class T>
	void RegisterScriptedEventListenerMethods(asIScriptEngine *engine, const char *c_name)
	{
		int r;
		r = engine->RegisterObjectMethod(c_name, "EventConnection@ AddEventListener(const rString &in, IEventListener@, bool)",
			asFUNCTIONPR(AddScriptedEventListener, (const Rocket::Core::String&, asIScriptObject*, bool, T*), EventConnection*), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Element::AddEventListener(event,IEventListener)");
		r = engine->RegisterObjectMethod(c_name, "EventConnection@ AddEventListener(const rString &in, IEventListener@)",
			asFUNCTIONPR(AddScriptedEventListener, (const Rocket::Core::String&, asIScriptObject*, T*), EventConnection*), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Element::AddEventListener(event,IEventListener)");

		/*r = engine->RegisterObjectMethod(c_name, "void RemoveEventListener(const rString &in, IEventListener@)",
			asFUNCTIONPR(RemoveScriptedEventListener, (const Rocket::Core::String&, asIScriptObject*, T*), void), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Element::RemoveEventListener(event,IEventListener) class");*/
	}

	void RegisterScriptedEventListenerMethods_ForElement(asIScriptEngine *engine, const char *c_name)
	{
		RegisterScriptedEventListenerMethods<Rocket::Core::Element>(engine, c_name);
	}

	void RegisterScriptedEventListenerMethods_ForContext(asIScriptEngine *engine)
	{
		RegisterScriptedEventListenerMethods<Rocket::Core::Context>(engine, "Context");
	}

}}
