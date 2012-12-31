/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_PRIMATIVE
#define H_ROCKET_AS_PRIMATIVE

#include <Rocket/Core.h>
#include <angelscript.h>

namespace Rocket { namespace AngelScript { namespace _registration_utils {

	//! Gets the AngelScript type name for a given primative type
	/*!
	 * If the type is unknown, name = "", otherwise name = 
	 * the name of the equivilant primative type in AngelScript.
	 */
	template <typename T>
	const char * as_primative_name()
	{
		return "";
	}

	template <>
	inline const char * as_primative_name<bool>()
	{
		return "bool";
	}

	template <>
	inline const char * as_primative_name<int>()
	{
		return "int";
	}

	template <>
	inline const char * as_primative_name<unsigned int>()
	{
		return "uint";
	}

	template <>
	inline const char * as_primative_name<short>()
	{
		return "int16";
	}

	template <>
	inline const char * as_primative_name<unsigned short>()
	{
		return "uint16";
	}

	template <>
	inline const char * as_primative_name<asINT64>()
	{
		return "int64";
	}

	template <>
	inline const char * as_primative_name<unsigned long long>()
	{
		return "uint64";
	}

	template <>
	inline const char * as_primative_name<float>()
	{
		return "float";
	}

	template <>
	inline const char * as_primative_name<double>()
	{
		return "double";
	}

}}}

#endif
