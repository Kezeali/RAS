/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_CONTROLS
#define H_ROCKET_AS_CONTROLSv

#include <angelscript.h>


namespace Rocket { namespace AngelScript {
	//! Functions / utilities for registering Controls
	namespace Controls {

		void RegisterControls(asIScriptEngine *engine);

	}
}}

#endif