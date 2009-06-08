/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_EVENTINSTANCER
#define H_ROCKET_AS_EVENTINSTANCER

#include <Rocket/Core.h>
#include <angelscript.h>

#include "ras_Decorator.h"

namespace Rocket { namespace AngelScript {

	class DecoratorInstancer : public Core::DecoratorInstancer
	{
	public:
		virtual Core::Decorator* InstanceDecorator(const EMP::Core::String& name, const Core::PropertyDictionary& properties);

		virtual void ReleaseDecorator(Core::Decorator* decorator);

		virtual void Release();
	};

	virtual Core::Decorator* DecoratorInstancer::InstanceDecorator(const EMP::Core::String& name, const Core::PropertyDictionary& properties)
	{
	}

	virtual void DecoratorInstancer::ReleaseDecorator(Core::Decorator* decorator)
	{}

	virtual void DecoratorInstancer::Release()
	{}

}}

#endif