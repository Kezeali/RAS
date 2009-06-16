/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../include/Rocket/AngelScript/Controls/ras_Controls.h"

#include "../include/Rocket/AngelScript/Controls/ras_ElementControlInterface.h"
#include "../include/Rocket/AngelScript/Controls/ras_DataFormatter.h"


namespace Rocket { namespace AngelScript {
	namespace Controls {

		RASCONTROLSDLL_API void RegisterControls(asIScriptEngine *engine)
		{
			ElementInterface::InitialiseAngelScriptInterface(engine);

			RegisterDataFormatter(engine);
		}

	}
}}
