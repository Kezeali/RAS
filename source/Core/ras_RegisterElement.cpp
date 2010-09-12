/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../../include/Rocket/AngelScript/Core/registration_utils/ras_RegisterElement.h"
#include <Rocket/Core.h>


namespace Rocket { namespace AngelScript { namespace _registration_utils {

	RASCOREDLL_API void documentShow_Default(Rocket::Core::ElementDocument *obj)
	{
		obj->Show();
	}

	RASCOREDLL_API void ElemAppendChild(Rocket::Core::Element *element, bool dom_element, Rocket::Core::Element *obj)
	{
		obj->AppendChild(element, dom_element);
		element->RemoveReference();
	}

	RASCOREDLL_API void ElemAppendChild_default(Rocket::Core::Element *element, Rocket::Core::Element *obj)
	{
		obj->AppendChild(element, true);
		element->RemoveReference();
	}

	RASCOREDLL_API bool ElemRemoveChild(Rocket::Core::Element *element, Rocket::Core::Element *obj)
	{
		bool success = obj->RemoveChild(element);
		element->RemoveReference();
		return success;
	}

	RASCOREDLL_API bool ElemDispatchEvent_default(const Rocket::Core::String &event, const Rocket::Core::Dictionary &parameters, Rocket::Core::Element *obj)
	{
		return obj->DispatchEvent(event, parameters);
	}

	RASCOREDLL_API bool ElemDispatchEvent_noparams(const Rocket::Core::String &event, Rocket::Core::Element *obj)
	{
		return obj->DispatchEvent(event, Rocket::Core::Dictionary());
	}

	RASCOREDLL_API void ElemScrollIntoView_default(Rocket::Core::Element *obj)
	{
		obj->ScrollIntoView();
	}

	RASCOREDLL_API Rocket::Core::Element* Element_GetElementById(const Rocket::Core::String &id, Rocket::Core::Element *obj)
	{
		Rocket::Core::Element *element = obj->GetElementById(id);
		if (element != nullptr)
			element->AddReference();
		return element;
	}

	RASCOREDLL_API Rocket::Core::ElementDocument* Element_GetOwnerDocument(Rocket::Core::Element *obj)
	{
		Rocket::Core::ElementDocument *document = obj->GetOwnerDocument();
		if (document != nullptr)
			document->AddReference();
		return document;
	}

}}}
