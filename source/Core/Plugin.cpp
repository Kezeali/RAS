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

	void CorePlugin::OnDocumentOpen(Rocket::Core::Context*, const Rocket::Core::String& document_path)
	{
		//InitialiseModule(engine, document_path.CString()); // This is done in ElementScriptableDocument now
	}

	CorePlugin* CorePlugin::instance = nullptr;

} }
