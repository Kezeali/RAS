/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_EVENTLISTENER
#define H_ROCKET_AS_EVENTLISTENER

#include "Config.h"

#include <angelscript.h>


namespace Rocket { namespace AngelScript {

	// The classes in this file are for EventListener classes / functions manually
	//  defined and registered in scripts.
	//  See ras_EventListenerInstancer.h for RML inline-event implementation / handling

	//extern void RegisterEventListenerInterface(asIScriptEngine *engine);

	//! Registers Add/RemoveEventListener methods for the given type
	/*!
	* Adds 
	* <code>Element::AddEventListener(const String &in event, IEventListener@ listener)</code>
	* and 
	* <code>Element::AddEventListener(const String &in event, const String &in callback_decl)</code>
	* so 'Element' must be registered as an ObjectType before this is called.
	*
	* \param[in] engine
	* Script engine to register the object methods with
	*
	* \param[in] c_name
	* The name of the Element derrived type these methods are being registerd for
	*/
	RASCOREDLL_API void RegisterElementEventListenerMethods(asIScriptEngine *engine, const char * c_name);

	//! Registeres Add/RemoveEventListener methods for "Context"
	void RegisterContextEventListenerMethods(asIScriptEngine *engine);

}}

#endif