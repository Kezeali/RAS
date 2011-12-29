/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_REGISTRATIONUTILS_VECTOR2
#define H_ROCKET_AS_REGISTRATIONUTILS_VECTOR2

#include <Rocket/Core.h>
#include <angelscript.h>

#include "../ras_Exception.h"

#include "ras_AngelScriptPrimativeTypes.h"


namespace Rocket { namespace AngelScript { namespace _registration_utils {
	
	//! Register an Rocket#Core#Vector2 class with components type T
	template <typename T>
	static void registerVector2(asIScriptEngine *engine, const std::string &script_name);
	//! Register an Rocket#Core#Vector2 class with components type T
	/*!
	* \param[in] engine
	* As engine to register the new Vector2<T> type with.
	*
	* \param[in] script_name
	* Name to register the Vector2 type with in AngelScript.
	* 
	* \param[in] T_name
	* Registered name of the primative type T in AngelScript.
	*/
	template <typename T>
	static void registerVector2(asIScriptEngine *engine, const std::string &script_name, const std::string &T_name);

	template <typename T>
	struct registerVector2_Utils
	{
		typedef Rocket::Core::Vector2<T> vector2_type;

		static void construct(vector2_type *ptr)
		{
			new(ptr) vector2_type();
		}

		static void construct_init(T x, T y, vector2_type *ptr)
		{
			new(ptr) vector2_type(x, y);
		}

	};

#include "ras_Vector2.inl"

}}}

#endif
