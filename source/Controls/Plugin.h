/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_CONTROLSPLUGIN
#define H_ROCKET_AS_CONTROLSPLUGIN

#include "../../include/Rocket/AngelScript/Controls/ras_Config.h"

#include <Rocket/Core.h>

#include <angelscript.h>

namespace Rocket { namespace AngelScript {
	namespace Controls
	{

		class ControlsPlugin : public Rocket::Core::Plugin
		{
		public:
			ControlsPlugin(asIScriptEngine* engine_)
				: engine(engine_)
			{
				engine->AddRef();

				instance = this;
			}

			virtual ~ControlsPlugin()
			{
				instance = nullptr;

				if (engine)
					engine->Release();
				engine = nullptr;
			}

			virtual int GetEventClasses()
			{
				return EVT_BASIC;
			}

			virtual void OnInitialise() 
			{
				if (engine)
					engine->Release();
				engine = nullptr;
			}

			virtual void OnShutdown() 
			{
				delete this;
			}

		private:
			asIScriptEngine* engine;

			static ControlsPlugin* instance;
		};

	}
} }

#endif
