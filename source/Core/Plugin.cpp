/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "Plugin.h"

#include "../../include/Rocket/AngelScript/Core/Core.h"
#include "../../include/Rocket/AngelScript/Core/EventListenerInstancer.h"
#include "../../include/Rocket/AngelScript/Core/ElementScriptableDocument.h"

#include <Rocket/Core/Plugin.h>
#include <Rocket/Core/Factory.h>

namespace Rocket { namespace AngelScript
{

	void CorePlugin::OnInitialise()
	{
		Rocket::Core::Factory::RegisterEventListenerInstancer(new Rocket::AngelScript::InlineEventListenerInstancer(engine))
			->RemoveReference();

		RegisterScriptableDocumentInstancer(engine);
	}

	void CorePlugin::OnDocumentLoad(Rocket::Core::ElementDocument* document)
	{
		InitialiseModule(engine, document->GetSourceURL().CString());
	}

	CorePlugin* CorePlugin::instance = nullptr;

} }
