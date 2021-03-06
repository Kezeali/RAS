/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../../include/Rocket/AngelScript/Core/Decorator.h"

#include "../../include/Rocket/AngelScript/Core/Exception.h"

#include <Rocket/Core/Decorator.h>
#include <Rocket/Core/Element.h>
#include <ScriptUtils/Inheritance/ScriptObjectWrapper.h>


namespace Rocket { namespace AngelScript {

	class ScriptedDecoratorDataHandle : public ScriptUtils::Inheritance::ScriptObjectWrapper
	{
	public:
		ScriptedDecoratorDataHandle(asIScriptObject *self);
	};

	// ScriptedDecorator
	ScriptedDecorator::ScriptedDecorator(asIScriptObject* self)
		: Rocket::Core::Decorator(),
		ScriptUtils::Inheritance::ScriptObjectWrapper(self, "IDecorator")
	{
	}

	Core::DecoratorDataHandle ScriptedDecorator::GenerateElementData(Core::Element* element)
	{
		ScriptUtils::Calling::Caller f = this->get_caller("IDecoratorData@ GenerateElementData(Element@)");
		if (f)
		{
			element->AddReference();
			asIScriptObject* data = *static_cast<asIScriptObject**>( f(element) );

			data->AddRef();
			return reinterpret_cast<Rocket::Core::DecoratorDataHandle>(data);
		}
		return (Core::DecoratorDataHandle)NULL;
	}

	void ScriptedDecorator::ReleaseElementData(Core::DecoratorDataHandle element_data)
	{
		ScriptUtils::Calling::Caller f = this->get_caller("void ReleaseElementData(IDecoratorData@)");
		if (f)
		{
			asIScriptObject* data = reinterpret_cast<asIScriptObject*>( element_data );
			data->AddRef();
			f(data);
			data->Release();
		}
	}

	void ScriptedDecorator::RenderElement(Core::Element* element, Core::DecoratorDataHandle element_data)
	{
		ScriptUtils::Calling::Caller f = this->get_caller("void RenderElement(Element@,IDecoratorData@)");
		if (f)
		{
			asIScriptObject *obj = reinterpret_cast<asIScriptObject*>(element_data);
			obj->AddRef();

			element->AddReference();
			f(element, element_data);
		}
	}

	// ScriptedDecoratorDataHandle
	ScriptedDecoratorDataHandle::ScriptedDecoratorDataHandle(asIScriptObject *self)
		: ScriptUtils::Inheritance::ScriptObjectWrapper(self, "IDecoratorData")
	{}

	void RegisterDecoratorInterfaces(asIScriptEngine *engine)
	{
		int r;
		r = engine->RegisterInterface("IDecoratorData");

		r = engine->RegisterInterface("IDecorator");
		r = engine->RegisterInterfaceMethod("IDecorator", "IDecoratorData@ GenerateElementData(Element@)");
		r = engine->RegisterInterfaceMethod("IDecorator", "void ReleaseElementData(IDecoratorData@)");
		r = engine->RegisterInterfaceMethod("IDecorator", "void RenderElement(Element@,IDecoratorData@)");
	}

}}
