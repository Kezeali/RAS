/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_CONTROLS
#define H_ROCKET_AS_CONTROLS

#include "ras_Config.h"

#include <angelscript.h>


namespace Rocket { namespace AngelScript {
	//! Functions / utilities for registering Controls
	namespace Controls {

		//! Register the script interface and plugin
		RASCONTROLSDLL_API void Initialise(asIScriptEngine* engine);

		//! Register the script interface
		void RegisterControls(asIScriptEngine *engine);

	}
}}

#endif