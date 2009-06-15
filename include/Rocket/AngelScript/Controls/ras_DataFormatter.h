/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_DATAFORMATTER
#define H_ROCKET_AS_DATAFORMATTER

#pragma once

#include <angelscript.h>

//namespace Rocket { namespace Core {
//	class Element;
//	class Context;
//}}


namespace Rocket { namespace AngelScript {

	//! Registers IDataFormatter
	void RegisterDataFormatterInterface(asIScriptEngine *engine);


	//! Registers AddDataFormatter, RemoveDataFormatter
	void RegisterDataFormatterCreator(asIScriptEngine *engine);

	void RegisterDataFormatter(asIScriptEngine *engine);

}}

#endif