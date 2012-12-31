/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "Plugin.h"

#include "../../include/Rocket/AngelScript/Controls/Controls.h"

#include <Rocket/Core/Plugin.h>
#include <Rocket/Core/Factory.h>

namespace Rocket { namespace AngelScript {
	namespace Controls
	{

		ControlsPlugin* ControlsPlugin::instance = nullptr;

	}
} }
