/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "Plugin.h"

#include "../../include/Rocket/AngelScript/Core/ras_Core.h"
#include "../../include/Rocket/AngelScript/Core/ras_EventListenerInstancer.h"
#include "../../include/Rocket/AngelScript/Core/ras_ElementDocument.h"

#include <Rocket/Core/Plugin.h>
#include <Rocket/Core/Factory.h>

namespace Rocket { namespace AngelScript
{

	void CorePlugin::OnInitialise()
	{
		Rocket::Core::Factory::RegisterEventListenerInstancer(new Rocket::AngelScript::InlineEventListenerInstancer(engine))
			->RemoveReference();

		RegisterScriptableDocumentInstancer(engine);

		if (engine)
			engine->Release();
		engine = nullptr;
	}

	void CorePlugin::OnDocumentLoad(Rocket::Core::ElementDocument* document)
	{
		InitialiseModule(engine, document->GetSourceURL().CString());
	}

	CorePlugin* CorePlugin::instance = nullptr;

} }
