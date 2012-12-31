/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_DECORATORINSTANCER
#define H_ROCKET_AS_DECORATORINSTANCER

#include <Rocket/Core.h>
#include <angelscript.h>

#include "Decorator.h"

#include <ScriptUtils/Calling/Caller.h>

namespace Rocket { namespace AngelScript {

	void RegisterScriptedDecorator(asIScriptEngine *engine);

}}

#endif