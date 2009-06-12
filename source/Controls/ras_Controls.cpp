/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../include/Rocket/AngelScript/Controls/ras_Controls.h"

#include "../include/Rocket/AngelScript/Controls/ras_ElementControlInterface.h"


namespace Rocket { namespace AngelScript {
	namespace Controls {

		void RegisterControls(asIScriptEngine *engine)
		{
			ElementInterface::InitialiseAngelScriptInterface(engine);
		}

	}
}}
