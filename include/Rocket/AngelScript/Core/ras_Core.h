/*
* libRocket AngleScript binding
* By Elliot Hayward
* :)
*/

#ifndef H_ROCKET_AS_CORE
#define H_ROCKET_AS_CORE

#include "ras_Config.h"

#include <Rocket/Core.h>
#include <angelscript.h>

#include "ras_Exception.h"

namespace Rocket {
	//! Methods / Utils for binding Rocket to AngelScript
	namespace AngelScript {}
}


namespace Rocket { namespace AngelScript {

	//void ActivateScriptGeneration();

	//! Registers main Rocket types
	//! \todo TODO: rewrite Element bindings to use AngelScript 1.17.1's property accessor support (to be more simmilar to the python plugin)
	RASCOREDLL_API void RegisterCore(asIScriptEngine *engine);

	//! Sets up the given module to use certain Rocket functionality
	/*!
	* Loads ScriptElement code into the given module, so custom element classes can
	* be written in AngelScript.<br>
	* Initializes and registers the InlineEventListenerInstancer for executing in-line
	* AngelScript code in RML events.
	*/
	RASCOREDLL_API void InitialiseModule(asIScriptEngine *engine, const char *module_name);

	//! Allow conversion from the built-in string type to the Rocket string types
	/*!
	 * Registers automatic & explicit conversion behaviours / constructors
	 * from the given built-in string type (must be based on std::string)
	 * to Rocket#Core#String and Rocket#Core#String.
	 *
	 * \remarks
	 * This is a wrapper for StringConversion<std_converter>#Register()
	 *
	 * \todo
	 * Allow a custom conversion callback to be passed for string types that aren't
	 * implicitly convertable to std::string
	 *
	 * \param[in] engine
	 * AngelScript engine to register the conversion / cast functions with
	 *
	 * \param[in] builtin_string_typename
	 * The AngelScript typename of the string type to allow conversion from
	 *
	 * \param[in] allow_implicit
	 * If true, implict conversion operators will be registerd for the given type
	 *
	 * \see StringConversion
	 */
	RASCOREDLL_API void RegisterStringConversion(asIScriptEngine *engine, const std::string &builtin_string_typename, bool allow_implicit = true);

	//! Converts between std#string and Rocket#Core#String
	struct RASCOREDLL_API std_converter
	{
		typedef std::string string_type;

		string_type operator() (const Rocket::Core::String& from) const;

		Rocket::Core::String operator() (const string_type& from) const;
	};

	//! String conversion registration util
	/*!
	* \tparam _Converter
	* The conversion function - used to convert from string_typename (see Register()) to 
	* rString and vice-versa.
	*/
	template <class _Converter = std_converter>
	class StringConversion
	{
	public:
		//! Registers conversion (type-casting) to and from rString to the given string-type
		/*!
		* \param[in] engine
		* AngelScript engine to register the cast behaviours with.
		*
		* \param[in] string_typename
		* The name of the string type to convert from/to - must be already registered
		*
		* \param[in] allow_implicit
		* Set to true to register implicit cast behaviours
		*/
		static void Register(asIScriptEngine *engine, const std::string &string_typename, bool allow_implicit = true)
		{
			bool refType = false;
			{
				int typeId = engine->GetTypeIdByDecl(string_typename.c_str());
				if (typeId >= 0)
				{
					asIObjectType *type = engine->GetObjectTypeById(typeId);
					if (type->GetSize() == 0)
						refType = true;
					else if (type->GetFlags() & asOBJ_REF)
						refType = true;
				}
			}

			if (refType)
				Register_RefType(engine, string_typename, allow_implicit);
			else
				Register_ValueType(engine, string_typename, allow_implicit);
		}

		static void Register_ValueType(asIScriptEngine *engine, const std::string &string_typename, bool allow_implicit = true)
		{
			int r;
			// Explicit conversion constructor from <built-in> to Rocket::Core::String (registered as rString)
			r = engine->RegisterObjectBehaviour("rString",
				asBEHAVE_CONSTRUCT,
				("void f("+string_typename+")").c_str(),
				asFUNCTION(EString_construct_from_string),
				asCALL_CDECL_OBJLAST);
			if (r < 0)
				throw Exception("Couldn't register explicit "+string_typename+" conversion constructor for rString");

			// Explicit conversion constructor from rString to <built-in>
			/*r = engine->RegisterObjectBehaviour(string_typename.c_str(),
			asBEHAVE_CONSTRUCT,
			"void f(rString)",
			asFUNCTION(string_construct_from_EString),
			asCALL_CDECL_OBJLAST);
			if (r < 0)
			throw Exception("Couldn't register Rocket String type");*/

			if (allow_implicit)
			{
				// Implicit cast from <built-in> to rString
				r = engine->RegisterObjectBehaviour(string_typename.c_str(),
					asBEHAVE_IMPLICIT_VALUE_CAST, "rString f()",
					asFUNCTION(stringToEString), asCALL_CDECL_OBJFIRST);
				if (r < 0)
					throw Exception("Couldn't register implicit string cast operator for " + string_typename);

				// Implicit cast from rString to <built-in>
				r = engine->RegisterObjectBehaviour("rString", asBEHAVE_IMPLICIT_VALUE_CAST,
					(string_typename + " f()").c_str(),
					asFUNCTION(eStringToString), asCALL_CDECL_OBJFIRST);
				if (r < 0)
					throw Exception("Couldn't register implicit string cast operator for rString");
			}
		}

		static void Register_RefType(asIScriptEngine *engine, const std::string &string_typename, bool allow_implicit = true)
		{
			int r;
			// Explicit conversion constructor from <built-in> to rString
			r = engine->RegisterObjectBehaviour("rString",
				asBEHAVE_CONSTRUCT,
				("void f("+string_typename+"&in)").c_str(),
				asFUNCTION(EString_construct_from_string),
				asCALL_CDECL_OBJLAST);
			if (r < 0)
				throw Exception("Couldn't register explicit "+string_typename+" conversion constructor for rString");

			if (allow_implicit)
			{
				r = engine->RegisterObjectMethod("rString",
					("rString& opAssign(const "+string_typename+"&in)").c_str(),
					asFUNCTION(EString_assign_string),
					asCALL_CDECL_OBJLAST);
				if (r < 0)
					throw Exception("Couldn't register "+string_typename+" assignment for rString");

				r = engine->RegisterObjectMethod("rString",
					("rString& opAddAssign(const "+string_typename+"&in)").c_str(),
					asFUNCTION(EString_addassign_string),
					asCALL_CDECL_OBJLAST);
				if (r < 0)
					throw Exception("Couldn't register rString::+= "+string_typename+"@");
			}
		}

		static void EString_construct_from_string(typename _Converter::string_type str, Rocket::Core::String *);
		//static void RString_construct_from_string(typename _Converter::string_type str, Rocket::Core::String *);

		static Rocket::Core::String& EString_assign_string(typename _Converter::string_type str, Rocket::Core::String *);
		static Rocket::Core::String& EString_addassign_string(typename _Converter::string_type str, Rocket::Core::String *);

		static Rocket::Core::String add_eString_string(Rocket::Core::String left, typename _Converter::string_type right);
		static Rocket::Core::String add_string_eString(typename _Converter::string_type left, Rocket::Core::String right);

		//static void string_construct_from_EString(Rocket::Core::String, std::string *);
		//static void string_construct_from_RString(Rocket::Core::String, std::string *);

		//static Rocket::Core::String stringToRString(typename _Converter::string_type *from)
		//{
		//	_Converter converter;
		//	return Rocket::Core::String( converter(*from) );
		//}
		static Rocket::Core::String stringToEString(typename _Converter::string_type *from)
		{
			_Converter converter;
			return converter(*from);
		}
		static typename _Converter::string_type eStringToString(Rocket::Core::String *from)
		{
			_Converter converter;
			return converter(*from);
		}

	};

	template <class _Converter>
	void StringConversion<_Converter>::EString_construct_from_string(typename _Converter::string_type str, Rocket::Core::String *ptr)
	{
		new(ptr) Rocket::Core::String(stringToEString(&str));
	}

	//template <class _Converter>
	//void StringConversion<_Converter>::RString_construct_from_string(typename _Converter::string_type str, Rocket::Core::String *ptr)
	//{
	//	new(ptr) Rocket::Core::String(stringToEString(&str));
	//}

	template <class _Converter>
	Rocket::Core::String& StringConversion<_Converter>::EString_assign_string(typename _Converter::string_type str, Rocket::Core::String *obj)
	{
		return obj->Assign(stringToEString(&str));
	}

	template <class _Converter>
	Rocket::Core::String& StringConversion<_Converter>::EString_addassign_string(typename _Converter::string_type str, Rocket::Core::String *obj)
	{
		return obj->Append(stringToEString(&str));
	}

	template <class _Converter>
	Rocket::Core::String StringConversion<_Converter>::add_eString_string(Rocket::Core::String left, typename _Converter::string_type right)
	{
		return left + stringToEstring(&right);
	}

	template <class _Converter>
	Rocket::Core::String StringConversion<_Converter>::add_string_eString(typename _Converter::string_type left, Rocket::Core::String right)
	{
		return stringToEString(&left) + right;
	}

	//void string_construct_from_EString(Rocket::Core::String str, std::string *ptr)
	//{
	//	new(ptr) std::string(str.CString());
	//}

	//template <_Converter>
	//Rocket::Core::String stringToEString<_Converter>(_Converter::string_type* from)
	//{
	//	_Converter converter;
	//	return converter(*script_string);
	//}

	//Rocket::Core::String stringToRString(std::string* script_string)
	//{
	//	Rocket::Core::String rString(script_string->c_str());
	//	return rString;
	//}

	//template <_Converter>
	//_Converter::string_type eStringToString<_Converter>(Rocket::Core::String *obj)
	//{
	//}

}}

#endif
