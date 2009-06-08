/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_REGISTRATIONUTILS_VARIANT
#define H_ROCKET_AS_REGISTRATIONUTILS_VARIANT

#include <Rocket/Core.h>
#include <angelscript.h>

#include <string>

#include "../ras_Exception.h"


namespace Rocket { namespace AngelScript { namespace _registration_utils {

	//! Registers EMP#Core#Variant
	void registerVariant(asIScriptEngine *engine);
	//! Registers EMP#Core#Dictionary
	void registerDictionary(asIScriptEngine *engine);

	template <typename T>
	T dictionaryGet(const EMP::Core::String &key, const T &default_value, EMP::Core::Dictionary *obj)
	{
		return obj->Get(key, default_value);
	}

	template <typename T>
	void variantSet(const T &value, EMP::Core::Variant *obj)
	{
		obj->Set(value);
	}

	//! Register Get/Set methods for Variant and types that use Variant.
	/*! 
	 * Registers e_Variant#Get_<script_typename>
	 * Registers e_Dictionary#Get(e_String key, <script_typename> default_value)
	 */
	template <typename T>
	void registerVariantGetSet(asIScriptEngine *engine, const std::string &script_typename)
	{
		using namespace EMP::Core;

		int r;
		r = engine->RegisterObjectMethod("e_Variant",
			C_STR(script_typename+" Get_"+script_typename+"()"),
			asMETHOD(Variant, Get<T>),
			asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Variant::Get<"+script_typename+">");

		r = engine->RegisterObjectMethod("e_Dictionary",
			std::string(script_typename+" Get(const e_String &in, const "+script_typename+" &in)").c_str(),
			asFUNCTION(dictionaryGet<T>),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Dictionary::Get<"+script_typename+">");

		r = engine->RegisterObjectMethod("e_Variant",
			C_STR("void Set(const "+script_typename+" &in)"),
			asFUNCTION(variantSet<T>),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Variant::Set(const "+script_typename+" &)");

		r = engine->RegisterObjectMethod("e_Dictionary",
			C_STR("void Set(const e_String &in, const "+script_typename+" &in)"),
			asMETHODPR(Dictionary, Set<T>, (const String&, const T&), void),
			asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Dictionary::Set<"+script_typename+">");
	}

}}}

#endif
