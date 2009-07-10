/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_EVENTCONNECTION
#define H_ROCKET_AS_EVENTCONNECTION

#include <angelscript.h>

#include <EMP/Core/ScriptInterface.h>

namespace Rocket { namespace Core {
	class Element;
	class Context;
	class EventListener;
}}

namespace Rocket { namespace AngelScript {

	//! Automatically removes EventListeners when going out of scope
	class EventConnection : public EMP::Core::ScriptInterface
	{
	public:
		//! Constructor
		/*!
		* \param[in] event_type
		* Event type of the listener
		*
		* \param[in] listener
		* The listener instance itself
		*
		* \param[in] in_capture_phase
		* Whether the listener is bound to the capture phase
		*/
		EventConnection(const EMP::Core::String &event_type, Rocket::Core::EventListener *listener, bool in_capture_phase);
		//! Destructor
		virtual ~EventConnection();

		//! Removes the event listener held by this connection from the element / context
		/*!
		* Usually called by the destructor, but may be called earlier if
		* immediate removal of the listener is required.
		*/
		//virtual void RemoveListener() = 0;
		virtual void RemoveListener();

	protected:
		EMP::Core::String m_EventType;
		Rocket::Core::EventListener *m_Listener;
		bool m_InCapturePhase;
	};

	//! EventConnection derived template type
	template <class T>
	class EventConnectionTemplate : public EventConnection
	{
	public:
		EventConnectionTemplate(T *target, const EMP::Core::String &event_type, Rocket::Core::EventListener *listener, bool in_capture_phase);

		virtual void RemoveListener();

	protected:
		T *m_Target;
	};

	template <class T>
	EventConnectionTemplate<T>::EventConnectionTemplate(T *target, const EMP::Core::String &event_type, Rocket::Core::EventListener *listener, bool in_capture_phase)
		: EventConnection(event_type, listener, in_capture_phase),
		m_Target(target)
	{}

	template <class T>
	void EventConnectionTemplate<T>::RemoveListener()
	{
		m_Target->RemoveEventListener(m_EventType, m_Listener, m_InCapturePhase);
	}

	////! EventConnection derived type for Elements
	//class ElementEventConnection : public EventConnection
	//{
	//public:
	//	ElementEventConnection(Rocket::Core::Element *element, const EMP::Core::String &event_type, Rocket::Core::EventListener *listener, bool in_capture_phase);

	//	void RemoveListener();

	//protected:
	//	Rocket::Core::Element *m_Element;
	//};

	////! EventConnection derived type for contexts
	//class ContextEventConnection : public EventConnection
	//{
	//public:
	//	//! Constructor
	//	//! \see EventConnection
	//	ContextEventConnection(Rocket::Core::Context *context, const EMP::Core::String &event_type, Rocket::Core::EventListener *listener, bool in_capture_phase);
	//	void RemoveListener();

	//protected:
	//	Rocket::Core::Context *m_Context;
	//};

	void RegisterEventConnectionType(asIScriptEngine *engine);

}}

#endif
