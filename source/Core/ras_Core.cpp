/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../../include/Rocket/AngelScript/Core/ras_Core.h"
#include "../../include/Rocket/AngelScript/Core/registration_utils/ras_RegistrationUtils.h"
#include "../../include/Rocket/AngelScript/Core/registration_utils/ras_RegisterVariantType.h"
#include "../../include/Rocket/AngelScript/Core/registration_utils/ras_EMPSTL.h"
#include "../../include/Rocket/AngelScript/Core/registration_utils/ras_Vector2.h"
#include "../../include/Rocket/AngelScript/Core/ras_ElementInstancer.h"
#include "../../include/Rocket/AngelScript/Core/ras_DecoratorInstancer.h"
#include "../../include/Rocket/AngelScript/Core/ras_EventListenerInstancer.h"
#include "../../include/Rocket/AngelScript/Core/ras_ScriptedEventListener.h"
#include "../../include/Rocket/AngelScript/Core/ras_EventConnection.h"
#include "../../include/Rocket/AngelScript/Core/ras_ElementDocument.h"
#include "Plugin.h"

#include "../../include/Rocket/AngelScript/Core/ScriptElement.h"

#include <ScriptUtils/Inheritance/RegisterConversion.h>

namespace Rocket { namespace AngelScript
{

	RASCOREDLL_API void Initialise(asIScriptEngine* engine)
	{
		RegisterCore(engine);

		CorePlugin* plugin = new CorePlugin(engine);
		Rocket::Core::RegisterPlugin(plugin);
	}

	Rocket::Core::Context* CreateCtxWrapper(const Rocket::Core::String &name, const Rocket::Core::Vector2i &dimen)
	{
		return Rocket::Core::CreateContext(name, dimen);
	}

	RASCOREDLL_API void RegisterCore(asIScriptEngine *engine)
	{
		using namespace _registration_utils;

		const char* scriptNamespace = "Rocket";

		engine->SetDefaultNamespace(scriptNamespace);

		// Flags which can be passed to Document::Show()
		registerFocusFlagsEnum(engine);

		registerKeyIdentifierEnum(engine);
		registerKeyModifierEnum(engine);

		registeString(engine);

		registerVector2<int>(engine, "Vector2i");
		registerVector2<float>(engine, "Vector2f");

		registerVariant(engine);
		registerProperty(engine);
		registerDictionary(engine);
		registerPropertyDictionary(engine);

		// Register types
		registerType::referenceCountable<Rocket::Core::Context>(engine, "Context");
		registerType::referenceCountable<Rocket::Core::Event>(engine, "Event");
		//  Elements
		registerType::referenceCountable<Rocket::Core::Element>(engine, "Element");
		registerType::referenceCountable<Rocket::Core::ElementDocument>(engine, "ElementDocument");
		registerType::referenceCountable<Rocket::Core::ElementText>(engine, "ElementText");

		// Register Get/Set methods for Dictionary and Variant 
		//  (and some helper methods for classes that use Variant and
		//  Dictionary internally)
		registerVariantGetSet<bool>(engine, "bool");
		registerVariantGetSet<int>(engine, "int");
		registerVariantGetSet<float>(engine, "float");
		registerVariantGetSet<Rocket::Core::String>(engine, "String");
		//registerVariantGetSet<Rocket::Core::Vector2i>(engine, "Vector2i");
		registerVariantGetSet<Rocket::Core::Vector2f>(engine, "Vector2f");

		//  IEventListener
		RegisterEventListenerInterface(engine);
		// EventConnection
		RegisterEventConnectionType(engine);

		// EventListenerInstancer (simply holds a reference, so it
		//  gets deleted when the module gets destroyed - see InitialiseModule
		//  for where this is used.)
		//registerType::referenceCountable<Rocket::Core::EventListenerInstancer>(engine, "__EventListenerInstancer");

		// Register STL containers
		registerStlVector<Rocket::Core::Element*>(engine, "ElementList", "Element@");
		registerStlVector<Rocket::Core::String>(engine, "StringList", "String");
		registerStlMap<Rocket::Core::String, Rocket::Core::Property>(engine, "PropertyMap", "String", "Property");

		// Register type members
		registerContextMembers(engine);

		//  Elements
		//   Basic Element
		registerElementMembers<Rocket::Core::Element>(engine, "Element");

		//   ElementDocument
		registerElementMembers<Rocket::Core::ElementDocument>(engine, "ElementDocument");
		registerDocumentMembers<Rocket::Core::ElementDocument>(engine, "ElementDocument");
		//    Register base conversion
		ScriptUtils::Inheritance::RegisterBaseOf<Rocket::Core::Element, Rocket::Core::ElementDocument>(engine, "Element", "ElementDocument");

		//   ElementText
		registerElementMembers<Rocket::Core::ElementText>(engine, "ElementText");
		//registerElementTextMembers<Core::ElementText>(engine, "ElementText");
		//    Register base conversions
		ScriptUtils::Inheritance::RegisterBaseOf<Core::Element, Core::ElementText>(engine, "Element", "ElementText");

		// ElementInstancer for ScriptElement wrapper
		Rocket::AngelScript::RegisterElementInstancer(engine);
		// Unwrap Element@ to IElement@ (which can be casted to ScriptElement@)
		Rocket::AngelScript::RegisterScriptElementConversion(engine);

		// Event
		registerEventMembers(engine);

		// Decorator
		RegisterScriptedDecorator(engine);
		RegisterDecoratorInterfaces(engine);

		int r;
		r = engine->RegisterGlobalFunction("Context@ CreateContext(const String &in, const Vector2i &in)", asFUNCTION(CreateCtxWrapper), asCALL_CDECL);
		if (r < 0)
			throw Exception("Failed to bind CreateContext(string, vector)");

		r = engine->RegisterGlobalFunction("Context& GetContext(const String &in)", asFUNCTIONPR(Rocket::Core::GetContext, (const Rocket::Core::String&), Rocket::Core::Context*), asCALL_CDECL);
		if (r < 0)
			throw Exception("Failed to bind GetContext(string)");
		r = engine->RegisterGlobalFunction("Context& GetContext(int)", asFUNCTIONPR(Rocket::Core::GetContext, (int), Rocket::Core::Context*), asCALL_CDECL);
		if (r < 0)
			throw Exception("Failed to bind GetContext(int)");

		r = engine->RegisterGlobalFunction("int GetNumContext()", asFUNCTION(Rocket::Core::GetNumContexts), asCALL_CDECL);
		if (r < 0)
			throw Exception("Failed to bind GetNumContexts()");

		r = engine->RegisterGlobalFunction("String GetVersion()", asFUNCTION(Rocket::Core::GetVersion), asCALL_CDECL);
		if (r < 0)
			throw Exception("Failed to bind GetVersion()");

		engine->SetDefaultNamespace("");
	}

	RASCOREDLL_API void InitialiseModule(asIScriptEngine *engine, const char *module_name)
	{
		int r = AddElementsScriptSection(engine, module_name);
		ROCKET_ASSERTMSG(r >= 0, "Failed to add ScriptElement code to the given module");
	}

	std_converter::string_type std_converter::operator ()(const Rocket::Core::String &from) const
	{
		std::string to(from.CString());
		return to;
	}

	Rocket::Core::String std_converter::operator ()(const std_converter::string_type &from) const
	{
		Rocket::Core::String to(from.c_str());
		return to;
	}

	RASCOREDLL_API void RegisteStringConversion(asIScriptEngine *engine, const std::string &builtin_string_typename, bool allow_implicit)
	{
		StringConversion<std_converter>::Register(engine, builtin_string_typename, allow_implicit);
	}

}}
