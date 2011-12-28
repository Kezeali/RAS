/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../../include/Rocket/AngelScript/Core/ras_DecoratorInstancer.h"

#include "../../include/Rocket/AngelScript/Core/ras_Exception.h"

#include <Rocket/Core/DecoratorInstancer.h>


namespace Rocket { namespace AngelScript {

	class ScriptedDecoratorInstancer : public Core::DecoratorInstancer
	{
	public:
		ScriptedDecoratorInstancer(asIScriptEngine *engine, int type_id, const Rocket::Core::String& class_name);

	public:
		virtual Core::Decorator* InstanceDecorator(const Rocket::Core::String& name, const Core::PropertyDictionary& properties);

		virtual void ReleaseDecorator(Core::Decorator* decorator);

		virtual void Release();

	private:
		asIScriptEngine *m_Engine;
		int m_TypeId;
		Rocket::Core::String m_ClassName;

		Rocket::Core::String m_ParamsStr;
		Rocket::Core::StringList m_Params;
	};

	ScriptedDecoratorInstancer::ScriptedDecoratorInstancer(asIScriptEngine *engine, int type_id, const Rocket::Core::String& name)
		: m_Engine(engine),
		m_TypeId(type_id),
		m_ClassName(name)
	{
	}

	Core::Decorator* ScriptedDecoratorInstancer::InstanceDecorator(const Rocket::Core::String& name, const Core::PropertyDictionary& properties)
	{
		//m_TypeId = m_Engine->GetTypeIdByDecl(m_ClassName.CString());
		// TODO: check type is valid (i.e. typeId is >= 0)

		//asIObjectType *type = m_Engine->GetObjectTypeById(typeId);

		//ScriptUtils::Calling::Caller callFactory = ScriptUtils::Calling::Caller::FactoryCaller(type, "const PropertyDictionary&in");
		//asIScriptObject *obj = *static_cast<asIScriptObject**>( callFactory(&properties) );

		//Rocket::Core::STL::map<Rocket::Core::String, Rocket::Core::String> registeredParams;

		Core::PropertyMap propMap = properties.GetProperties();

		/*for (Rocket::Core::StringList::iterator it = m_Params.begin(), end = m_Params.end(); it != end; ++it)
		{
			const Core::Property *prop = properties.GetProperty(*it);
			if (prop != NULL)
				registeredParams[*it] = prop->Get<Rocket::Core::String>();
		}
		callInitialize(&registeredParams)*/

		asIScriptObject *obj = static_cast<asIScriptObject*>( m_Engine->CreateScriptObject(m_TypeId) );
		if (obj == NULL)
			return NULL;

		ScriptUtils::Calling::Caller callInitialize(obj, "void Initialize(const PropertyMap&in)");
		callInitialize(&propMap);

		return new ScriptedDecorator(obj);
	}

	void ScriptedDecoratorInstancer::ReleaseDecorator(Core::Decorator* decorator)
	{
		delete decorator;
	}

	void ScriptedDecoratorInstancer::Release()
	{
		delete this;
	}

	void RegisterScriptedDecoratorInstancer(const Rocket::Core::String &rml, const Rocket::Core::String &class_name)
	{
		asIScriptContext *ctx = asGetActiveContext();
		if (ctx != NULL)
		{
			asIScriptEngine *engine = ctx->GetEngine();
			int funcId = ctx->GetFunction()->GetId();
			const char *moduleName = engine->GetFunctionById(funcId)->GetModuleName();
			asIScriptModule *module = engine->GetModule(moduleName); // Why can't I just go ctx->GetModule()?!
			int typeId = module->GetTypeIdByDecl(class_name.CString());
			if (typeId <= 0)
			{
				Rocket::Core::Log::Message(Rocket::Core::Log::LT_WARNING,
					"Can't register decorator-instancer for %s: class %s doesn't exist", rml.CString(), class_name.CString());
				return;
			}

			Rocket::Core::Factory::RegisterDecoratorInstancer(rml, new ScriptedDecoratorInstancer(engine, typeId, class_name));
		}
	}

	void AddDecoratorProperty(const Rocket::Core::String &decorator_name/*, etc...*/)
	{
		//Rocket::Core::Factory::GetElementInstancer
	}

	void RegisterScriptedDecorator(asIScriptEngine *engine)
	{
		engine->RegisterGlobalFunction("void RegisterDecorator(const rString &in, const rString &in)",
			asFUNCTION(RegisterScriptedDecoratorInstancer), asCALL_CDECL);
	}

}}
