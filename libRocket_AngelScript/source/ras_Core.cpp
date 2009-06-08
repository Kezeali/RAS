/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../include/ras_Core.h"
#include "../include/registration_utils/ras_RegistrationUtils.h"
#include "../include/registration_utils/ras_RegisterVariantType.h"
#include "../include/registration_utils/ras_EMPSTL.h"
#include "../include/registration_utils/ras_Vector2.h"

#include <Inheritance/RegisterConversion.h>


namespace Rocket { namespace AngelScript {

	Rocket::Core::Context* CreateCtxWrapper(const EMP::Core::String &name, const EMP::Core::Vector2i &dimen)
	{
		return Rocket::Core::CreateContext(name, dimen);
	}

	void RegisterRocketCore(asIScriptEngine *engine)
	{
		using namespace _registration_utils;

		// Rocket::Core::String
		registerRString(engine);
		// EMP::Core::String
		registerEString(engine);

		registerVector2<int>(engine, "e_Vector2i");
		registerVector2<float>(engine, "e_Vector2f");

		registerVariant(engine);
		registerDictionary(engine);
		// Register Get/Set methods for Dictionary and Variant
		registerVariantGetSet<EMP::Core::String>(engine, "e_String");
		//registerVariantGetSet<EMP::Core::Vector2i>(engine, "e_Vector2i");
		registerVariantGetSet<EMP::Core::Vector2f>(engine, "e_Vector2f");

		// Register types
		registerType::referenceCountable<Rocket::Core::Context>(engine, "Context");
		registerType::referenceCountable<Rocket::Core::Event>(engine, "Event");
		registerType::interface<Rocket::Core::EventListener>(engine, "EventListener");
		//  Elements
		registerType::referenceCountable<Rocket::Core::Element>(engine, "Element");
		registerType::referenceCountable<Rocket::Core::ElementDocument>(engine, "Document");
		registerType::referenceCountable<Rocket::Core::ElementText>(engine, "ElementText");

		// Register STL containers
		registerStlVector<Rocket::Core::Element*>(engine, "ElementList", "Element");

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


		// Event stuff
		registerEventMembers(engine);
		registerEventListenerMembers(engine);


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

	static void constructEString_convert_stdstring(std::string, EMP::Core::String *);
	static void constructRString_convert_stdstring(std::string, Rocket::Core::String *);
	static EMP::Core::String stringToEString(std::string*);
	static Rocket::Core::String stringToRString(std::string*);

	void RegisterStringConversion(asIScriptEngine *engine, const std::string &string_typename, bool allow_implicit)
	{
		int r;
		// Explicit conversion constructor from <built-in> to e_String
		r = engine->RegisterObjectBehaviour("e_String",
			asBEHAVE_CONSTRUCT,
			"void f(string)",
			asFUNCTION(constructEString_convert_stdstring),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register EMP String type");
		// Explicit conversion constructor from <built-in> to r_String
		r = engine->RegisterObjectBehaviour("r_String",
			asBEHAVE_CONSTRUCT,
			"void f(string)",
			asFUNCTION(constructRString_convert_stdstring),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register explicit string conversion constructor for r_String");

		if (allow_implicit)
		{
			// Implicit cast from <built-in> to e_String behaviour
			r = engine->RegisterObjectBehaviour(string_typename.c_str(), asBEHAVE_IMPLICIT_VALUE_CAST, "e_String f()", asFUNCTION(stringToEString), asCALL_CDECL_OBJFIRST);
			if (r < 0)
				throw Exception("Couldn't register implicit string cast operator for " + string_typename);
			// Implicit cast from <built-in> to r_String behaviour
			r = engine->RegisterObjectBehaviour(string_typename.c_str(), asBEHAVE_IMPLICIT_VALUE_CAST, "r_String f()", asFUNCTION(stringToRString), asCALL_CDECL_OBJFIRST);
			if (r < 0)
				throw Exception("Couldn't register implicit string cast operator for " + string_typename);
		}
	}

	void constructEString_convert_stdstring(std::string str, EMP::Core::String *ptr)
	{
		new(ptr) EMP::Core::String(str.c_str());
	}

	void constructRString_convert_stdstring(std::string str, Rocket::Core::String *ptr)
	{
		new(ptr) Rocket::Core::String(str.c_str());
	}

	// TODO: convert these to template methods so the built-in
	//  string type doesn't have to be convertable to std::string
	EMP::Core::String stringToEString(std::string* script_string)
	{
		EMP::Core::String eString(script_string->c_str());
		return eString;
	}

	Rocket::Core::String stringToRString(std::string* script_string)
	{
		Rocket::Core::String rString(script_string->c_str());
		return rString;
	}

}}
