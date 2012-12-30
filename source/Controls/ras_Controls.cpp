/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../../include/Rocket/AngelScript/Controls/ras_Controls.h"

#include "../../include/Rocket/AngelScript/Controls/ras_ElementControlInterface.h"
#include "../../include/Rocket/AngelScript/Controls/ras_DataFormatter.h"
#include "../../include/Rocket/AngelScript/Controls/ras_DataSource.h"


namespace Rocket { namespace AngelScript {
	namespace Controls {

		RASCONTROLSDLL_API void RegisterControls(asIScriptEngine *engine)
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
