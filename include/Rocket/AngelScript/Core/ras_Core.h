/*
* libRocket AngleScript binding
* By Elliot Hayward
* :)
*/

#ifndef H_ROCKET_AS_CORE
#define H_ROCKET_AS_CORE

#include <Rocket/Core.h>
#include <angelscript.h>

#include "ras_Exception.h"

namespace Rocket {
	//! Methods / Utils for binding Rocket to AngelScript
	namespace AngelScript {}
}

///////////////////////////////////////////////////
// TODO: Formatter and DLL (for controls and core)
/////////////////////////////////////////////////

namespace Rocket { namespace AngelScript {

	//void ActivateScriptGeneration();

	//! Registers main Rocket types
	void RegisterCore(asIScriptEngine *engine);

	//! Allow conversion from the built-in string type to the Rocket string types
	/*!
	 * Registers automatic & explicit conversion behaviours / constructors
	 * from the given built-in string type (must be based on std::string)
	 * to Rocket#Core#String and EMP#Core#String.
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
	void RegisterStringConversion(asIScriptEngine *engine, const std::string &builtin_string_typename, bool allow_implicit = true);

	struct std_converter
	{
		typedef std::string string_type;

		string_type operator() (const EMP::Core::String& from) const;

		EMP::Core::String operator() (const string_type& from) const;
	};

	//! String conversion registration util
	/*!
	* \tparam _Converter
	* The conversion function - used to convert from string_typename (see Register()) to 
	* e_String and vice-versa.
	*/
	template <class _Converter = std_converter>
	class StringConversion
	{
	public:
		//! Registers conversion (type-casting) to and from e_String to the given string-type
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
			int r;
			// Explicit conversion constructor from <built-in> to e_String
			r = engine->RegisterObjectBehaviour("e_String",
				asBEHAVE_CONSTRUCT,
				"void f(string)",
				asFUNCTION(EString_construct_from_string),
				asCALL_CDECL_OBJLAST);
			if (r < 0)
				throw Exception("Couldn't register EMP String type");
			// Explicit conversion constructor from <built-in> to r_String
			r = engine->RegisterObjectBehaviour("r_String",
				asBEHAVE_CONSTRUCT,
				"void f(string)",
				asFUNCTION(RString_construct_from_string),
				asCALL_CDECL_OBJLAST);
			if (r < 0)
				throw Exception("Couldn't register explicit string conversion constructor for r_String");

			// Explicit conversion constructor from e_String to <built-in>
			/*r = engine->RegisterObjectBehaviour(string_typename.c_str(),
				asBEHAVE_CONSTRUCT,
				"void f(e_String)",
				asFUNCTION(string_construct_from_EString),
				asCALL_CDECL_OBJLAST);
			if (r < 0)
				throw Exception("Couldn't register EMP String type");*/

			if (allow_implicit)
			{
				// Implicit cast from <built-in> to e_String
				r = engine->RegisterObjectBehaviour(string_typename.c_str(),
					asBEHAVE_IMPLICIT_VALUE_CAST, "e_String f()",
					asFUNCTION(stringToEString), asCALL_CDECL_OBJFIRST);
				if (r < 0)
					throw Exception("Couldn't register implicit string cast operator for " + string_typename);
				// Implicit cast from <built-in> to r_String
				r = engine->RegisterObjectBehaviour(string_typename.c_str(),
					asBEHAVE_IMPLICIT_VALUE_CAST, "r_String f()",
					asFUNCTION(stringToRString), asCALL_CDECL_OBJFIRST);
				if (r < 0)
					throw Exception("Couldn't register implicit string cast operator for " + string_typename);

				// Implicit cast from e_String to <built-in>
				r = engine->RegisterObjectBehaviour("e_String", asBEHAVE_IMPLICIT_VALUE_CAST,
					(string_typename + " f()").c_str(),
					asFUNCTION(eStringToString), asCALL_CDECL_OBJFIRST);
				if (r < 0)
					throw Exception("Couldn't register implicit string cast operator for e_String");
			}
		}

		static void EString_construct_from_string(std::string, EMP::Core::String *);
		static void RString_construct_from_string(std::string, Rocket::Core::String *);

		//static void string_construct_from_EString(Rocket::Core::String, std::string *);
		//static void string_construct_from_RString(Rocket::Core::String, std::string *);

		static Rocket::Core::String stringToRString(typename _Converter::string_type *from)
		{
			_Converter converter;
			return Rocket::Core::String( converter(*from) );
		}
		static EMP::Core::String stringToEString(typename _Converter::string_type *from)
		{
			_Converter converter;
			return converter(*from);
		}
		static typename _Converter::string_type eStringToString(EMP::Core::String *from)
		{
			_Converter converter;
			return converter(*from);
		}

	};

	template <class _Converter>
	void StringConversion<_Converter>::EString_construct_from_string(std::string str, EMP::Core::String *ptr)
	{
		new(ptr) EMP::Core::String(str.c_str());
	}

	template <class _Converter>
	void StringConversion<_Converter>::RString_construct_from_string(std::string str, Rocket::Core::String *ptr)
	{
		new(ptr) Rocket::Core::String(str.c_str());
	}

	//void string_construct_from_EString(Rocket::Core::String str, std::string *ptr)
	//{
	//	new(ptr) std::string(str.CString());
	//}

	//template <_Converter>
	//EMP::Core::String stringToEString<_Converter>(_Converter::string_type* from)
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
	//_Converter::string_type eStringToString<_Converter>(EMP::Core::String *obj)
	//{
	//}

}}

#endif
