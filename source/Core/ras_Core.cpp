/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../include/Rocket/AngelScript/Core/ras_Core.h"
#include "../include/Rocket/AngelScript/Core/registration_utils/ras_RegistrationUtils.h"
#include "../include/Rocket/AngelScript/Core/registration_utils/ras_RegisterVariantType.h"
#include "../include/Rocket/AngelScript/Core/registration_utils/ras_EMPSTL.h"
#include "../include/Rocket/AngelScript/Core/registration_utils/ras_Vector2.h"
#include "../include/Rocket/AngelScript/Core/ras_ScriptedEventListener.h"
#include "../include/Rocket/AngelScript/Core/ras_DataSource.h"
#include "../include/Rocket/AngelScript/Core/ras_DecoratorInstancer.h"



#include <Inheritance/RegisterConversion.h>


namespace Rocket { namespace AngelScript {

	Rocket::Core::Context* CreateCtxWrapper(const EMP::Core::String &name, const EMP::Core::Vector2i &dimen)
	{
		return Rocket::Core::CreateContext(name, dimen);
	}

	void RegisterCore(asIScriptEngine *engine)
	{
		using namespace _registration_utils;

		// Rocket::Core::String
		registerRString(engine);
		// EMP::Core::String
		registerEString(engine);

		registerVector2<int>(engine, "e_Vector2i");
		registerVector2<float>(engine, "e_Vector2f");

		registerVariant(engine);
		registerProperty(engine);
		registerDictionary(engine);
		registerPropertyDictionary(engine);
		// Register Get/Set methods for Dictionary and Variant
		registerVariantGetSet<EMP::Core::String>(engine, "e_String");
		//registerVariantGetSet<EMP::Core::Vector2i>(engine, "e_Vector2i");
		registerVariantGetSet<EMP::Core::Vector2f>(engine, "e_Vector2f");

		// Register types
		registerType::referenceCountable<Rocket::Core::Context>(engine, "Context");
		registerType::referenceCountable<Rocket::Core::Event>(engine, "Event");
		//  Elements
		registerType::referenceCountable<Rocket::Core::Element>(engine, "Element");
		registerType::referenceCountable<Rocket::Core::ElementDocument>(engine, "Document");
		registerType::referenceCountable<Rocket::Core::ElementText>(engine, "ElementText");

		//  IEventListener
		RegisterEventListenerInterface(engine);

		// Register STL containers
		registerStlVector<Rocket::Core::Element*>(engine, "ElementList", "Element@");
		registerStlVector<EMP::Core::String>(engine, "StringList", "e_String");
		registerStlMap<EMP::Core::String, Rocket::Core::Property>(engine, "PropertyMap", "e_String", "r_Property");

		// Register type members
		registerContextMembers(engine);

		//  Elements
		//   Basic Element
		registerElementMembers<Rocket::Core::Element>(engine, "Element");

		//   ElementDocument
		registerElementMembers<Rocket::Core::ElementDocument>(engine, "Document");
		registerDocumentMembers<Rocket::Core::ElementDocument>(engine, "Document");
		//    Register base conversion
		ScriptUtils::Inheritance::RegisterBaseOf<Rocket::Core::Element, Rocket::Core::ElementDocument>(engine, "Element", "Document");

		//   ElementText
		registerElementMembers<Rocket::Core::ElementText>(engine, "ElementText");
		//registerElementTextMembers<Core::ElementText>(engine, "ElementText");
		//    Register base conversions
		ScriptUtils::Inheritance::RegisterBaseOf<Core::Element, Core::ElementText>(engine, "Element", "ElementText");

		// Event
		registerEventMembers(engine);

		// DataSource
		RegisterDataSource(engine);

		// Decorator
		RegisterScriptedDecorator(engine);
		RegisterDecoratorInterfaces(engine);


		int r;
		r = engine->RegisterGlobalFunction("Context@ CreateContext(const e_String &in, const e_Vector2i &in)", asFUNCTION(CreateCtxWrapper), asCALL_CDECL);
		if (r < 0)
			throw Exception("Failed to bind CreateContext(string, vector)");

		r = engine->RegisterGlobalFunction("Context& GetContext(const e_String &in)", asFUNCTIONPR(Rocket::Core::GetContext, (const EMP::Core::String&), Rocket::Core::Context*), asCALL_CDECL);
		if (r < 0)
			throw Exception("Failed to bind GetContext(string)");
		r = engine->RegisterGlobalFunction("Context& GetContext(int)", asFUNCTIONPR(Rocket::Core::GetContext, (int), Rocket::Core::Context*), asCALL_CDECL);
		if (r < 0)
			throw Exception("Failed to bind GetContext(int)");

		r = engine->RegisterGlobalFunction("int GetNumContext()", asFUNCTION(Rocket::Core::GetNumContexts), asCALL_CDECL);
		if (r < 0)
			throw Exception("Failed to bind GetNumContexts()");

		r = engine->RegisterGlobalFunction("e_String GetVersion()", asFUNCTION(Rocket::Core::GetVersion), asCALL_CDECL);
		if (r < 0)
			throw Exception("Failed to bind GetVersion()");
	}

	std_converter::string_type std_converter::operator ()(const EMP::Core::String &from) const
	{
		std::string to(from.CString());
		return to;
	}

	EMP::Core::String std_converter::operator ()(const std_converter::string_type &from) const
	{
		EMP::Core::String to(from.c_str());
		return to;
	}

	void RegisterStringConversion(asIScriptEngine *engine, const std::string &builtin_string_typename, bool allow_implicit)
	{
		StringConversion<std_converter>::Register(engine, builtin_string_typename, allow_implicit);
	}

}}
