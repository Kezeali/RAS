/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../../include/Rocket/AngelScript/Core/registration_utils/ras_RegisterVariantType.h"

#include <cstdint>


namespace Rocket { namespace AngelScript { namespace _registration_utils {

	void PropertyCtor(Rocket::Core::Property *ptr)
	{
		new(ptr) Rocket::Core::Property();
	}

	void PropertyDtor(Rocket::Core::Property *obj)
	{
		obj->~Property();
	}

	void registerProperty(asIScriptEngine *engine)
	{
		int r;
		r = engine->RegisterObjectType("r_Property", sizeof(Rocket::Core::Property), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
		if (r < 0)
			throw Exception("Couldn't register Property type");

		//  CTOR
		r = engine->RegisterObjectBehaviour("r_Property", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(PropertyCtor), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Property type");

		//  Destructor
		r = engine->RegisterObjectBehaviour("r_Property", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(PropertyDtor), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Property type");
	}

	void constructVariant(Rocket::Core::Variant *mem)
	{
		new(mem) Rocket::Core::Variant();
	}

	void constructVariant_copy(const Rocket::Core::Variant &copy, Rocket::Core::Variant *mem)
	{
		new(mem) Rocket::Core::Variant(copy);
	}

	void destructVariant(Rocket::Core::Variant *mem)
	{
		mem->~Variant();
	}

	// TODO:
	void constructVariant_variabletype(void *data, int typeId, Rocket::Core::Variant *obj)
	{
		if (typeId & asTYPEID_BOOL)
			new(obj) Rocket::Core::Variant(*static_cast<bool*>(data));
		else if (typeId & asTYPEID_INT8)
			new(obj) Rocket::Core::Variant(*static_cast<std::int8_t*>(data));
		else if (typeId & asTYPEID_INT16)
			new(obj) Rocket::Core::Variant(*static_cast<std::int16_t*>(data));
		else if (typeId & asTYPEID_INT32)
			new(obj) Rocket::Core::Variant(*static_cast<std::int32_t*>(data));
		//else if (typeId & asTYPEID_INT64)
		//	new(obj) Rocket::Core::Variant(*static_cast<asINT64*>(data));

		else if (typeId & asTYPEID_UINT16)
			new(obj) Rocket::Core::Variant(*static_cast<std::int16_t*>(data));
		//else if (typeId & asTYPEID_UINT32)
		//	new(obj) Rocket::Core::Variant(*static_cast<unsigned long*>(data));

		else if (typeId & asTYPEID_FLOAT)
			new(obj) Rocket::Core::Variant(*static_cast<float*>(data));
		else if (typeId & asTYPEID_DOUBLE)
			new(obj) Rocket::Core::Variant(static_cast<float>(*static_cast<double*>(data)));

		else if (typeId & asTYPEID_OBJHANDLE)
			new(obj) Rocket::Core::Variant(data);

		else
		{
			asIScriptContext *context = asGetActiveContext();
			if (context != NULL)
				context->SetException("Variant can't contain the given type.");
		}
	}

	Rocket::Core::Variant *variantAssign(const Rocket::Core::Variant &copy, Rocket::Core::Variant *obj)
	{
		*obj = copy;
		return obj;
	}

	void registerVariant(asIScriptEngine *engine)
	{
		using namespace Rocket::Core;

		int r;
		r = engine->RegisterObjectType("e_Variant", sizeof(Rocket::Core::Variant), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
		if (r < 0)
			throw Exception("Couldn't register Variant type");

		// Behaviours
		//  CTOR
		r = engine->RegisterObjectBehaviour("e_Variant", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(constructVariant), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Variant type");
		r = engine->RegisterObjectBehaviour("e_Variant", asBEHAVE_CONSTRUCT, "void f(const e_Variant &in)", asFUNCTION(constructVariant_copy), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Variant type");

		//  Destructor
		r = engine->RegisterObjectBehaviour("e_Variant", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(destructVariant), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Variant type");
		
		//  Assignment
		r = engine->RegisterObjectMethod("e_Variant", "e_Variant &opAssign(const e_Variant &in)", asFUNCTION(variantAssign), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Variant type");

		// Methods
		r = engine->RegisterObjectMethod("e_Variant", "bool GetInto(rString &out)", asMETHODPR(Rocket::Core::Variant, GetInto, (Rocket::Core::String&) const, bool), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Variant::GetInto(String)");
		r = engine->RegisterObjectMethod("e_Variant", "bool GetInto(int &out)", asMETHODPR(Rocket::Core::Variant, GetInto, (int&) const, bool), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Variant::GetInto(int)");
		r = engine->RegisterObjectMethod("e_Variant", "bool GetInto(float &out)", asMETHODPR(Rocket::Core::Variant, GetInto, (float&) const, bool), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Variant::GetInto(float)");
	}

	void constructDictionary(Rocket::Core::Dictionary *obj)
	{
		new(obj) Rocket::Core::Dictionary();
	}

	void initDictionary_tokenstring(const Rocket::Core::String &entries, Rocket::Core::Dictionary *obj)
	{
		using namespace Rocket::Core;

		String::size_type token_pos = 0, token_length = 0;
		while (true)
		{
			token_length = entries.Find(":", token_pos);
			if (token_length == String::npos)
				break;

			String key = StringUtilities::StripWhitespace(
				entries.Substring(token_pos, token_length)
				);

			token_pos = token_length+1;
			token_length = entries.Find(",", token_pos);

			if (!key.Empty())
			{
				String value = entries.Substring(token_pos, token_length);
				value = StringUtilities::StripWhitespace(value);

				obj->Set(key, value);
			}

			if (token_length == String::npos)
				break; // Reached the end of the string

			// Next token pos
			token_pos = token_length+1;
		}
	}

	void constructDictionary_tokenstring(const Rocket::Core::String &entries, Rocket::Core::Dictionary *obj)
	{
		new(obj) Rocket::Core::Dictionary();

		initDictionary_tokenstring(entries, obj);
	}

	void destructDictionary(Rocket::Core::Dictionary *obj)
	{
		obj->~Dictionary();
	}

	Rocket::Core::Dictionary *dictionaryAssign(const Rocket::Core::Dictionary &copy, Rocket::Core::Dictionary *obj)
	{
		*obj = copy;
		return obj;
	}

	Rocket::Core::Variant *dictionaryIndex(const Rocket::Core::String &key, Rocket::Core::Dictionary *obj)
	{
		Rocket::Core::Variant *value = obj->Get(key);
		if (value == NULL)
		{
			asIScriptContext* context = asGetActiveContext();
			if( context )
				context->SetException("Dictionary key invalid.");
			return NULL;
		}

		return value;
	}

	void registerDictionary(asIScriptEngine *engine)
	{
		int r;
		r = engine->RegisterObjectType("e_Dictionary", sizeof(Rocket::Core::Dictionary), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
		if (r < 0)
			throw Exception("Couldn't register Dictionary type");

		// Behaviours
		//  CTOR
		r = engine->RegisterObjectBehaviour("e_Dictionary", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(constructDictionary), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Dictionary type");
		r = engine->RegisterObjectBehaviour("e_Dictionary", asBEHAVE_CONSTRUCT, "void f(const rString &in)", asFUNCTION(constructDictionary_tokenstring), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Dictionary type");

		//  Destructor
		r = engine->RegisterObjectBehaviour("e_Dictionary", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(destructDictionary), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Dictionary type");
		
		//  Assignment
		r = engine->RegisterObjectMethod("e_Dictionary", "e_Dictionary &opAssign(const e_Dictionary &in)", asFUNCTION(dictionaryAssign), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Dictionary type");

		//  Index
		r = engine->RegisterObjectMethod("e_Dictionary", "e_Variant& opIndex(const rString &in)", asFUNCTION(dictionaryIndex), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Dictionary type");

		// Methods
		r = engine->RegisterObjectMethod("e_Dictionary", "bool GetInto(rString &out)", asMETHODPR(Rocket::Core::Dictionary, GetInto, (const Rocket::Core::String&, Rocket::Core::String&) const, bool), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Dictionary::GetInto(String)");
		r = engine->RegisterObjectMethod("e_Dictionary", "bool GetInto(int &out)", asMETHODPR(Rocket::Core::Dictionary, GetInto, (const Rocket::Core::String&, int&) const, bool), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Dictionary::GetInto(int)");
		r = engine->RegisterObjectMethod("e_Dictionary", "bool GetInto(float &out)", asMETHODPR(Rocket::Core::Dictionary, GetInto, (const Rocket::Core::String&, float&) const, bool), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Dictionary::GetInto(float)");
	}

}}}
