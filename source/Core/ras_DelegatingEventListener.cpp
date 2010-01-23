/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../include/Rocket/AngelScript/Core/ras_DelegatingEventListener.h"

#include "../include/Rocket/AngelScript/Core/ras_Exception.h"
#include "../include/Rocket/AngelScript/Core/ras_EventConnection.h"

#include <Rocket/Core.h>

#include <ScriptUtils/Inheritance/ScriptObjectWrapper.h>
#include <ScriptUtils/Calling/Caller.h>


namespace Rocket { namespace AngelScript {

	//! Passes an event to a registered method
	class DelegatingEventListener : public Rocket::Core::EventListener
	{
	public:
		//! Ctor - event listener that calls a module-level fn.
		DelegatingEventListener(asIScriptModule *module, const std::string &callback_decl);
		//! Ctor - event listener that calls a object method
		DelegatingEventListener(asIScriptObject *object, const std::string &callback_decl);

		//! Calls the callback fn.
		virtual void ProcessEvent(Rocket::Core::Event& event);

		virtual void OnDetach(Rocket::Core::Element *element);

	private:
		ScriptUtils::Calling::Caller m_EventCallbackCaller;
		std::string m_Decl;
	};

	DelegatingEventListener::DelegatingEventListener(asIScriptModule *module, const std::string &callback_decl)
		: m_EventCallbackCaller(module, callback_decl.c_str()),
		m_Decl(callback_decl)
	{
	}

	DelegatingEventListener::DelegatingEventListener(asIScriptObject *object, const std::string &callback_decl)
		: m_EventCallbackCaller(object, callback_decl.c_str()),
		m_Decl(callback_decl)
	{
	}

	void DelegatingEventListener::ProcessEvent(Rocket::Core::Event &event)
	{
		if (m_EventCallbackCaller.ok())
		{
			event.AddReference();
			m_EventCallbackCaller(&event);
		}
	}

	//typedef std::tr1::shared_ptr<DelegatingEventListener> DelegatingEventListenerPtr;
	typedef std::tr1::unordered_map<std::string, DelegatingEventListener*> ListenerCallbackMap;
	static ListenerCallbackMap listenerCallbacks;

	void DelegatingEventListener::OnDetach(Rocket::Core::Element *element)
	{
		listenerCallbacks.erase(m_Decl);
		delete this;
	}

	//! Makes an event listener object that calls the given script fn.
	/*!
	* This must be called during script execution, as it finds the function
	* module by checking the active context.
	*/
	DelegatingEventListener *Make_DelegatingEventListener(const EMP::Core::String &callback_decl)
	{
		asIScriptContext *ctx = asGetActiveContext();
		if (ctx != NULL)
		{
			asIScriptEngine *engine = ctx->GetEngine();
			const char *moduleName = engine->GetFunctionDescriptorById( ctx->GetCurrentFunction() )->GetModuleName();
			
			asIScriptModule *module = engine->GetModule(moduleName);

			return new DelegatingEventListener(module, callback_decl.CString());
		}
		else
			return NULL;
	}

	template <class T>
	EventConnection *AddDelegatingEventListener(const EMP::Core::String &event_type, const EMP::Core::String &callback_decl, bool in_capture_phase, T *obj)
	{
		DelegatingEventListener *listener = Make_DelegatingEventListener(callback_decl);
		if (listener)
		{
			obj->AddEventListener(event_type, listener);

			//listenerCallbacks[callback_decl.CString()] = listener;
			return new EventConnectionTemplate<T>(obj, event_type, listener, in_capture_phase);
		}
		else
			return NULL;
	}

	template <class T>
	EventConnection *AddDelegatingEventListener(const EMP::Core::String &event_type, const EMP::Core::String &callback_decl, T *obj)
	{
		return AddDelegatingEventListener(event_type, callback_decl, false, obj);
	}

	template <class T>
	void RemoveDelegatingEventListener(const EMP::Core::String &event, const EMP::Core::String &callback_decl, T *obj)
	{
		ListenerCallbackMap::iterator _where = listenerCallbacks.find(callback_decl.CString());
		if (_where != listenerCallbacks.end())
		{
			obj->RemoveEventListener(event, _where->second);

			// The following line is commented out because the map entry is 
			//  removed in the listener's OnDetach() method
			//listenerCallbacks.erase(_where);
		}
	}

	template <class T>
	void RegisterDelegatingEventListenerMethods(asIScriptEngine *engine, const char *c_name)
	{
		int r;
		r = engine->RegisterObjectMethod(c_name, "EventConnection@ AddEventListener(const e_String &in, const e_String &in, bool)",
			asFUNCTIONPR(AddDelegatingEventListener, (const EMP::Core::String&, const EMP::Core::String&, bool, T*), EventConnection*), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Element::AddEventListener(event, callback-fn)");
		r = engine->RegisterObjectMethod(c_name, "EventConnection@ AddEventListener(const e_String &in, const e_String &in)",
			asFUNCTIONPR(AddDelegatingEventListener, (const EMP::Core::String&, const EMP::Core::String&, T*), EventConnection*), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Element::AddEventListener(event, callback-fn)");

		//r = engine->RegisterObjectMethod(c_name, "void RemoveEventListener(const e_String &in, const e_String &in)",
		//	asFUNCTIONPR(RemoveDelegatingEventListener, (const EMP::Core::String&, const EMP::Core::String&, T*), void), asCALL_CDECL_OBJLAST);
		//if (r < 0)
		//	throw Exception("Couldn't register Element::RemoveEventListener(event, callback-fn)");

		//r = engine->RegisterObjectMethod(c_name, "void RemoveAllEventListeners()",
		//	asFUNCTIONPR(RemoveAllDelegatingEventListeners, (const EMP::Core::String&, const EMP::Core::String&, T*), void), asCALL_CDECL_OBJLAST);
		//if (r < 0)
		//	throw Exception("Couldn't register Element::RemoveAllEventListeners(event, callback-fn)");
	}

	void RegisterDelegatingEventListenerMethods_ForElement(asIScriptEngine *engine, const char *c_name)
	{
		RegisterDelegatingEventListenerMethods<Rocket::Core::Element>(engine, c_name);
	}
	

	void RegisterDelegatingEventListenerMethods_ForContext(asIScriptEngine *engine)
	{
		RegisterDelegatingEventListenerMethods<Rocket::Core::Context>(engine, "Context");
	}

}}
