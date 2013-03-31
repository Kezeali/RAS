/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_EVENTLISTENERINSTANCER
#define H_ROCKET_AS_EVENTLISTENERINSTANCER

#include <Rocket/Core/EventListener.h>
#include <Rocket/Core/EventListenerInstancer.h>
#include <angelscript.h>


namespace Rocket { namespace AngelScript {

	//! Creates a script code executor for an inline (RML) defined event
	class InlineEventListenerInstancer : public Rocket::Core::EventListenerInstancer
	{
	public:
		//! CTOR
		InlineEventListenerInstancer(asIScriptEngine *engine);

		//! IEL
		Core::EventListener* InstanceEventListener(const Rocket::Core::String& value, Rocket::Core::Element* element);

		//! RLS (ACRONYMS!!)
		virtual void Release();

	protected:
		asIScriptEngine *m_Engine;

		int m_NextId;
	};

}}

#endif