/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_DECORATOR
#define H_ROCKET_AS_DECORATOR

#include <Rocket/Core.h>
#include <angelscript.h>


namespace Rocket { namespace AngelScript {

	class Decorator : public Rocket::Core::Decorator
	{
	public:
		virtual DecoratorDataHandle GenerateElementData(Core::Element* element);

		virtual void ReleaseElementData(Core::DecoratorDataHandle element_data);

		virtual void RenderElement(Core::Element* element, Core::DecoratorDataHandle element_data);
	};

	virtual Core::DecoratorDataHandle Decorator::GenerateElementData(Core::Element* element)
	{}

	virtual void Decorator::ReleaseElementData(Core::DecoratorDataHandle element_data)
	{}

	virtual void Decorator::RenderElement(Core::Element* element, Core::DecoratorDataHandle element_data)
	{}


}}

#endif
