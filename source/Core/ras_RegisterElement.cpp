/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../include/Rocket/AngelScript/Core/registration_utils/ras_RegisterElement.h"
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

	RASCOREDLL_API bool ElemDispatchEvent_default(const EMP::Core::String &event, const EMP::Core::Dictionary &parameters, Rocket::Core::Element *obj)
	{
		return obj->DispatchEvent(event, parameters);
	}

	RASCOREDLL_API bool ElemDispatchEvent_noparams(const EMP::Core::String &event, Rocket::Core::Element *obj)
	{
		return obj->DispatchEvent(event, EMP::Core::Dictionary());
	}

}}}
