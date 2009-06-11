/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_ELEMENTINSTANCER
#define H_ROCKET_AS_ELEMENTINSTANCER

#include <EMP/Core/String.h>
#include <EMP/Core/XMLParser.h>
#include <Rocket/Core/Element.h>
#include <Rocket/Core/ElementInstancer.h>
#include <Rocket/Core/Factory.h>
#include <angelscript.h>

#include <cstring>


namespace Rocket { namespace AngelScript {

	// ras_ElementInstancer contains class decl/defn. for the ElementWrapper instancer

	void RegisterElementInstancer(asIScriptEngine *engine);

	void RegisterScriptElementConversion(asIScriptEngine *engine);

	void BindElementInstancer(const EMP::Core::String &rml_name, asIScriptEngine *engine, int typeId);

}}

#endif
