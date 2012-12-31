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
#include <ScriptUtils/Calling/Caller.h>

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

	void CorePlugin::OnDocumentLoad(Rocket::Core::ElementDocument* document)
	{
		// Call the entry-point-esque OnDocumentLoad function in the document's module, if it has one
		auto scriptableDocument = dynamic_cast<ElementScriptableDocument*>(document);
		if (scriptableDocument != NULL)
		{
			auto module = engine->GetModule(scriptableDocument->GetModuleName().CString());
			if (module != nullptr)
			{
				ScriptUtils::Calling::Caller onScriptLoaded = ScriptUtils::Calling::Caller::Create(module, "void OnDocumentLoad()");
				if (onScriptLoaded)
					onScriptLoaded();
			}
		}
	}

	CorePlugin* CorePlugin::instance = nullptr;

} }
