/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_DATASOURCE
#define H_ROCKET_AS_DATASOURCE

#pragma once

#include <angelscript.h>

//namespace Rocket { namespace Core {
//	class Element;
//	class Context;
//}}


namespace Rocket { namespace AngelScript {

	//! Registers IDataSource
	void RegisterDataSourceInterface(asIScriptEngine *engine);


	//! Registers AddDataSource, RemoveDataSource
	void RegisterDataSourceCreator(asIScriptEngine *engine);

	void RegisterDataSource(asIScriptEngine *engine);

}}

#endif