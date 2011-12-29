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

	//! Registers Rocket#Core#Variant
	void registerVariant(asIScriptEngine *engine);
	//! Registers Rocket#Core#Property
	void registerProperty(asIScriptEngine *engine);
	//! Registers Rocket#Core#Dictionary
	void registerDictionary(asIScriptEngine *engine);

	template <typename T>
	T dictionaryGet(const Rocket::Core::String &key, const T &default_value, Rocket::Core::Dictionary *obj)
	{
		return obj->Get(key, default_value);
	}

	template <typename T>
	void variantSet(const T &value, Rocket::Core::Variant *obj)
	{
		obj->Set(value);
	}

	//! Register Get/Set methods for Variant and types that use Variant.
	/*! 
	 * Registers e_Variant#Get_<script_typename>
	 * Registers e_Dictionary#Get(rString key, <script_typename> default_value)
	 * Registers Element#GetAttribute (which thinly wraps e_Dictionary#Get)
	 * \todo Register Variant#GetInto(), Dictionary#GetInto() here
	 */
	template <typename T>
	void registerVariantGetSet(asIScriptEngine *engine, const std::string &script_typename)
	{
		using namespace Rocket::Core;

		int r;
		r = engine->RegisterObjectMethod("e_Variant",
			(script_typename+" Get_"+script_typename+"() const").c_str(),
			asMETHODPR(Variant, Get, (void) const, T),
			asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Variant::Get<"+script_typename+">");

		r = engine->RegisterObjectMethod("e_Dictionary",
			(script_typename+" Get(const rString &in, const "+script_typename+" &in) const").c_str(),
			asFUNCTION(dictionaryGet<T>),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Dictionary::Get<"+script_typename+">");

		r = engine->RegisterObjectMethod("e_Variant",
			("void Set(const "+script_typename+" &in)").c_str(),
			asFUNCTION(variantSet<T>),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Variant::Set(const "+script_typename+" &)");

		r = engine->RegisterObjectMethod("e_Dictionary",
			("void Set(const rString &in, const "+script_typename+" &in)").c_str(),
			asMETHODPR(Dictionary, Set<T>, (const String&, const T&), void),
			asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Dictionary::Set<"+script_typename+">");

		r = engine->RegisterObjectMethod("r_Property",
			(script_typename+" Get_"+script_typename+"() const").c_str(),
			asMETHODPR(Rocket::Core::Property, Get, (void) const, T),
			asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Property::Get<"+script_typename+">");

		r = engine->RegisterObjectMethod("Element",
			(script_typename+" GetAttribute(const rString &in, const "+script_typename+" &in) const").c_str(),
			asMETHODPR(Rocket::Core::Element, GetAttribute<T>, (const String&, const T&) const, T),
			asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Element::GetAttribute<"+script_typename+">");

		r = engine->RegisterObjectMethod("Element",
			("void SetAttribute(const rString &in, const "+script_typename+" &in) const").c_str(),
			asMETHODPR(Rocket::Core::Element, SetAttribute<T>, (const String&, const T&), void),
			asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Element::SetAttribute<"+script_typename+">");
	}


}}}

#endif
