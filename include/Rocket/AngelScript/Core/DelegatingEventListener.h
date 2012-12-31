/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_DELEGATINGEVENTLISTENER
#define H_ROCKET_AS_DELEGATINGEVENTLISTENER

#include <angelscript.h>

//namespace Rocket { namespace Core {
//	class Element;
//	class Context;
//}}


namespace Rocket { namespace AngelScript {

	//void AddDelegatingEventListener(const Rocket::Core::String &event, const Rocket::Core::String &callback_decl, Rocket::Core::Element *obj);
	//void RemoveDelegatingEventListener(const Rocket::Core::String &event, const Rocket::Core::String &callback_decl, Rocket::Core::Element *obj);
	//void AddDelegatingEventListener(const Rocket::Core::String &event, const Rocket::Core::String &callback_decl, Rocket::Core::Context *obj);
	//void RemoveDelegatingEventListener(const Rocket::Core::String &event, const Rocket::Core::String &callback_decl, Rocket::Core::Context *obj);

	//! Registers Element#AddEventListener() taking a function declaration string
	void RegisterDelegatingEventListenerMethods_ForElement(asIScriptEngine *engine, const char *c_name);

	//! Registers Context#AddEventListener() taking a function declaration string
	void RegisterDelegatingEventListenerMethods_ForContext(asIScriptEngine *engine);

}}

#endif