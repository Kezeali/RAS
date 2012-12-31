/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_SCRIPTEDEVENTLISTENER
#define H_ROCKET_AS_SCRIPTEDEVENTLISTENER

#include <angelscript.h>

//namespace Rocket { namespace Core {
//	class Element;
//	class Context;
//}}


namespace Rocket { namespace AngelScript {

	//! Registers IEventListener
	void RegisterEventListenerInterface(asIScriptEngine *engine);

	//void AddScriptedEventListener(const Rocket::Core::String &event, asIScriptObject *listener, Rocket::Core::Element *obj);
	//void RemoveScriptedEventListener(const Rocket::Core::String &event, asIScriptObject *listener, Rocket::Core::Element *obj);
	//void AddScriptedEventListener(const Rocket::Core::String &event, asIScriptObject *listener, Rocket::Core::Context *obj);
	//void RemoveScriptedEventListener(const Rocket::Core::String &event, asIScriptObject *listener, Rocket::Core::Context *obj);


	//! Registers Element#AddEventListener taking IEventListener
	void RegisterScriptedEventListenerMethods_ForElement(asIScriptEngine *engine, const char *c_name);

	//! Registers Context#AddEventListener taking IEventListener
	void RegisterScriptedEventListenerMethods_ForContext(asIScriptEngine *engine);

}}

#endif