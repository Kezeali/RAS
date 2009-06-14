/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_DECORATOR
#define H_ROCKET_AS_DECORATOR

#include <angelscript.h>

#include <Rocket/Core/Decorator.h>
#include <Inheritance/ScriptObjectWrapper.h>


namespace Rocket { namespace AngelScript {

	//! Registers IDecorator and IDecoratorData
	void RegisterDecoratorInterfaces(asIScriptEngine *engine);

	//! Decorator that calls script-object methods for it's implementation
	class ScriptedDecorator : public Rocket::Core::Decorator, public ScriptUtils::Inheritance::ScriptObjectWrapper
	{
	public:
		ScriptedDecorator(asIScriptObject *self);

	public:
		virtual Core::DecoratorDataHandle GenerateElementData(Core::Element* element);

		virtual void ReleaseElementData(Core::DecoratorDataHandle element_data);

		virtual void RenderElement(Core::Element* element, Core::DecoratorDataHandle element_data);
	};

}}

#endif
