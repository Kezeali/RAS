/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../include/Rocket/AngelScript/Core/ras_EventListener.h"

#include "../include/Rocket/AngelScript/Core/ras_ScriptedEventListener.h"
#include "../include/Rocket/AngelScript/Core/ras_DelegatingEventListener.h"


namespace Rocket { namespace AngelScript {

	//void RegisterEventListenerInterface(asIScriptEngine *engine)
	//{
	//	RegisterIEventListener(engine);
	//}

	RASCOREDLL_API void RegisterElementEventListenerMethods(asIScriptEngine *engine, const char *c_name)
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
