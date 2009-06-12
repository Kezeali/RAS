/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "ras_ElementControlInterface.h"


namespace Rocket { namespace AngelScript {
	namespace Controls {

		void RegisterControls(asIScriptEngine *engine)
		{
			ElementInterface::InitialiseAngelScriptInterface(engine);
		}

	}
}}
