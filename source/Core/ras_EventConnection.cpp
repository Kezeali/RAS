/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../../include/Rocket/AngelScript/Core/ras_EventConnection.h"

#include "../../include/Rocket/AngelScript/Core/registration_utils/ras_RegistrationUtils.h"


namespace Rocket { namespace AngelScript {

	EventConnection::EventConnection(const Rocket::Core::String &event_type, Rocket::Core::EventListener *listener, bool in_capture_phase)
		: m_EventType(event_type),
		m_Listener(listener),
		m_InCapturePhase(in_capture_phase)
	{
	}

	EventConnection::~EventConnection()
	{
		RemoveListener();
	}

	void EventConnection::RemoveListener()
	{
	}

	//ElementEventConnection::ElementEventConnection(Rocket::Core::Element *element, const Rocket::Core::String &event_type, Rocket::Core::EventListener *listener, bool in_capture_phase)
	//	: EventConnection(event_type, listener, in_capture_phase),
	//	m_Element(element)
	//{}

	//void ElementEventConnection::RemoveListener()
	//{
	//	m_Element->RemoveEventListener(m_EventType, m_Listener, m_InCapturePhase);
	//}

	//ContextEventConnection::ContextEventConnection(Rocket::Core::Context *context, const Rocket::Core::String &event_type, Rocket::Core::EventListener *listener, bool in_capture_phase)
	//	: EventConnection(event_type, listener, in_capture_phase),
	//	m_Context(context)
	//{}

	//void ContextEventConnection::RemoveListener()
	//{
	//	m_Context->RemoveEventListener(m_EventType, m_Listener, m_InCapturePhase);
	//}

	void RegisterEventConnectionType(asIScriptEngine *engine)
	{
		_registration_utils::registerType::referenceCountable<EventConnection>(engine, "EventConnection");
		engine->RegisterObjectMethod(
			"EventConnection", "void RemoveListener()",
			asMETHOD(EventConnection, RemoveListener), asCALL_THISCALL);
	}

}}
