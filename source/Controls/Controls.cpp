/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../../include/Rocket/AngelScript/Controls/Controls.h"

#include "../../include/Rocket/AngelScript/Controls/ElementControlInterface.h"
#include "../../include/Rocket/AngelScript/Controls/DataFormatter.h"
#include "../../include/Rocket/AngelScript/Controls/DataSource.h"
#include "Plugin.h"


namespace Rocket { namespace AngelScript {
	namespace Controls {

		RASCONTROLSDLL_API void Initialise(asIScriptEngine* engine)
		{
			RegisterControls(engine);

			//ControlsPlugin* plugin = new ControlsPlugin(engine);
			//Rocket::Core::RegisterPlugin(plugin);
		}

		void RegisterControls(asIScriptEngine *engine)
		{
			// TODO: make this Rocket::Controls, perhaps?
			engine->SetDefaultNamespace("Rocket");

			RegisterDataSource(engine);

			ElementInterface::InitialiseAngelScriptInterface(engine);

			RegisterDataFormatter(engine);

			engine->SetDefaultNamespace("");
		}

	}
}}
