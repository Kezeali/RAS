/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../include/ras_EventListener.h"

#include "../include/ras_ScriptedEventListener.h"
#include "../include/ras_DelegatingEventListener.h"


namespace Rocket { namespace AngelScript {

	//void RegisterEventListenerInterface(asIScriptEngine *engine)
	//{
	//	RegisterIEventListener(engine);
	//}

	void RegisterElementEventListenerMethods(asIScriptEngine *engine, const char *c_name)
	{
		RegisterScriptedEventListenerMethods_ForElement(engine, c_name);
		RegisterDelegatingEventListenerMethods_ForElement(engine, c_name);
	}

	void RegisterContextEventListenerMethods(asIScriptEngine *engine)
	{
		RegisterScriptedEventListenerMethods_ForContext(engine);
		RegisterDelegatingEventListenerMethods_ForContext(engine);
	}

}}
