/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../../include/Rocket/AngelScript/Core/EventListener.h"

#include "../../include/Rocket/AngelScript/Core/ScriptedEventListener.h"
#include "../../include/Rocket/AngelScript/Core/DelegatingEventListener.h"

#include "../../include/Rocket/AngelScript/Core/EventConnection.h"

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
