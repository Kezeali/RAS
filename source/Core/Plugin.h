/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_PLUGIN
#define H_ROCKET_AS_PLUGIN

#include "../../include/Rocket/AngelScript/Core/Config.h"

#include <Rocket/Core.h>

#include <angelscript.h>

namespace Rocket { namespace Core
{
	class ElementDocument;
} }

namespace Rocket { namespace AngelScript
{

	//! Plugin for injecting angelscript stuff
	class CorePlugin : public Rocket::Core::Plugin
	{
	public:
		CorePlugin(asIScriptEngine* engine_)
			: engine(engine_)
		{
			engine->AddRef();

			instance = this;
		}

		virtual ~CorePlugin()
		{
			instance = nullptr;

			if (engine)
				engine->Release();
			engine = nullptr;
		}

		virtual int GetEventClasses()
		{
			return EVT_BASIC | EVT_DOCUMENT;
		}

		virtual void OnInitialise();

		virtual void OnShutdown()
		{
			delete this;
		}

		virtual void OnDocumentOpen(Rocket::Core::Context* context, const Rocket::Core::String& document_path);

		virtual void OnDocumentLoad(Rocket::Core::ElementDocument* document);

	private:
		asIScriptEngine* engine;

		static CorePlugin* instance;
	};

} }

#endif
