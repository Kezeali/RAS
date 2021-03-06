/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_ELEMENTINSTANCER
#define H_ROCKET_AS_ELEMENTINSTANCER

#include <Rocket/Core/String.h>
#include <Rocket/Core/XMLParser.h>
#include <Rocket/Core/Element.h>
#include <Rocket/Core/ElementInstancer.h>
#include <Rocket/Core/Factory.h>
#include <angelscript.h>

#include <cstring>


namespace Rocket { namespace AngelScript {

	// ras_ElementInstancer contains class decl/defn. for the ElementWrapper instancer

	//! Registers all element instancer stuff
	void RegisterElementInstancer(asIScriptEngine *engine);

	//! Registers unwrap()
	/*!
	* \code
	* IElement@ unwrap(Element@)
	* \endcode
	*/
	void RegisterScriptElementConversion(asIScriptEngine *engine);

	//! Bind an element instancer (you don't need to use this)
	/*!
	* Usually the script equivilant of this function is called - this is provided for cases where
	* an instancer needs to be registered statically.
	*/
	void BindElementInstancer(const Rocket::Core::String &rml_name, asIScriptEngine *engine, int typeId);

}}

#endif
