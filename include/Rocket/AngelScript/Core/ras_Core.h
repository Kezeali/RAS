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

namespace Rocket { namespace AngelScript {

	//void ActivateScriptGeneration();

	//! Registers main Rocket types
	void RegisterCore(asIScriptEngine *engine);

	//! Allow conversion from the built-in string type to the Rocket string types
	/*!
	 * Registers automatic & explicit conversion behaviours / constructors
	 * from the given built-in string type to Rocket#Core#String and EMP#Core#String.
	 *
	 * \remarks
	 * Unfortuneately at this point the c++-type bound to the built-in string type
	 * given must be convertable to std::string (both scriptstdstring or
	 * CScriptString are)
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
	 */
	void RegisterStringConversion(asIScriptEngine *engine, const std::string &builtin_string_typename, bool allow_implicit = true);

}}

#endif
