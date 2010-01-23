/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../include/Rocket/AngelScript/Core/registration_utils/ras_RegisterVariantType.h"

#include <boost/tokenizer.hpp>


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

	void constructVariant(EMP::Core::Variant *mem)
	{
		new(mem) EMP::Core::Variant();
	}

	void constructVariant_copy(const EMP::Core::Variant &copy, EMP::Core::Variant *mem)
	{
		new(mem) EMP::Core::Variant(copy);
	}

	void destructVariant(EMP::Core::Variant *mem)
	{
		mem->~Variant();
	}

	// TODO:
	void constructVariant_variabletype(void *data, int typeId, EMP::Core::Variant *obj)
	{
		if (typeId & asTYPEID_BOOL)
			new(obj) EMP::Core::Variant(*static_cast<bool*>(data));
		else if (typeId & asTYPEID_INT8)
			new(obj) EMP::Core::Variant(*static_cast<char*>(data));
		else if (typeId & asTYPEID_INT16)
			new(obj) EMP::Core::Variant(*static_cast<short*>(data));
		else if (typeId & asTYPEID_INT32)
			new(obj) EMP::Core::Variant(*static_cast<long*>(data));
		//else if (typeId & asTYPEID_INT64)
		//	new(obj) EMP::Core::Variant(*static_cast<asINT64*>(data));

		else if (typeId & asTYPEID_UINT16)
			new(obj) EMP::Core::Variant(*static_cast<unsigned short*>(data));
		//else if (typeId & asTYPEID_UINT32)
		//	new(obj) EMP::Core::Variant(*static_cast<unsigned long*>(data));

		else if (typeId & asTYPEID_FLOAT)
			new(obj) EMP::Core::Variant(*static_cast<float*>(data));
		else if (typeId & asTYPEID_DOUBLE)
			new(obj) EMP::Core::Variant(*static_cast<float*>(data));

		else if (typeId & asTYPEID_OBJHANDLE)
			new(obj) EMP::Core::Variant(data);

		else
		{
			asIScriptContext *context = asGetActiveContext();
			if (context != NULL)
				context->SetException("Variant can't contain the given type.");
		}
	}

	EMP::Core::Variant *variantAssign(const EMP::Core::Variant &copy, EMP::Core::Variant *obj)
	{
		*obj = copy;
		return obj;
	}

	void registerVariant(asIScriptEngine *engine)
	{
		using namespace EMP::Core;

		int r;
		r = engine->RegisterObjectType("e_Variant", sizeof(EMP::Core::Variant), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
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
		r = engine->RegisterObjectMethod("e_Variant", "bool GetInto(e_String &out)", asMETHODPR(EMP::Core::Variant, GetInto, (EMP::Core::String&) const, bool), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Variant::GetInto(String)");
		r = engine->RegisterObjectMethod("e_Variant", "bool GetInto(int &out)", asMETHODPR(EMP::Core::Variant, GetInto, (int&) const, bool), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Variant::GetInto(int)");
		r = engine->RegisterObjectMethod("e_Variant", "bool GetInto(float &out)", asMETHODPR(EMP::Core::Variant, GetInto, (float&) const, bool), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Variant::GetInto(float)");
	}

	void constructDictionary(EMP::Core::Dictionary *obj)
	{
		new(obj) EMP::Core::Dictionary();
	}

	void initDictionary_tokenstring(const EMP::Core::String &entries, EMP::Core::Dictionary *obj)
	{
		using namespace EMP::Core;

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

	void constructDictionary_tokenstring(const EMP::Core::String &entries, EMP::Core::Dictionary *obj)
	{
		new(obj) EMP::Core::Dictionary();

		initDictionary_tokenstring(entries, obj);
	}

	void destructDictionary(EMP::Core::Dictionary *obj)
	{
		obj->~Dictionary();
	}

	EMP::Core::Dictionary *dictionaryAssign(const EMP::Core::Dictionary &copy, EMP::Core::Dictionary *obj)
	{
		*obj = copy;
		return obj;
	}

	EMP::Core::Variant *dictionaryIndex(const EMP::Core::String &key, EMP::Core::Dictionary *obj)
	{
		EMP::Core::Variant *value = obj->Get(key);
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
		r = engine->RegisterObjectType("e_Dictionary", sizeof(EMP::Core::Dictionary), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
		if (r < 0)
			throw Exception("Couldn't register Dictionary type");

		// Behaviours
		//  CTOR
		r = engine->RegisterObjectBehaviour("e_Dictionary", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(constructDictionary), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Dictionary type");
		r = engine->RegisterObjectBehaviour("e_Dictionary", asBEHAVE_CONSTRUCT, "void f(const e_String &in)", asFUNCTION(constructDictionary_tokenstring), asCALL_CDECL_OBJLAST);
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
		r = engine->RegisterObjectBehaviour("e_Dictionary", asBEHAVE_INDEX, "e_Variant& f(const e_String &in)", asFUNCTION(dictionaryIndex), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Dictionary type");

		// Methods
		r = engine->RegisterObjectMethod("e_Dictionary", "bool GetInto(e_String &out)", asMETHODPR(EMP::Core::Dictionary, GetInto, (const EMP::Core::String&, EMP::Core::String&) const, bool), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Dictionary::GetInto(String)");
		r = engine->RegisterObjectMethod("e_Dictionary", "bool GetInto(int &out)", asMETHODPR(EMP::Core::Dictionary, GetInto, (const EMP::Core::String&, int&) const, bool), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Dictionary::GetInto(int)");
		r = engine->RegisterObjectMethod("e_Dictionary", "bool GetInto(float &out)", asMETHODPR(EMP::Core::Dictionary, GetInto, (const EMP::Core::String&, float&) const, bool), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Dictionary::GetInto(float)");
	}

}}}
