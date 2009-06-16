/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_REGISTRATIONUTILS_REGISTERELEMENT
#define H_ROCKET_AS_REGISTRATIONUTILS_REGISTERELEMENT

#include "../ras_Config.h"

#include <string>

#include <Rocket/Core.h>
#include <angelscript.h>


namespace Rocket { namespace AngelScript { namespace _registration_utils {

	//! Registers members of Rocket#Core#Element
	template<class T>
	void registerElementMembers(asIScriptEngine *engine, const std::string& script_typename);
	//! Registers members of Rocket#Core#ElementDocument
	template<class T>
	void registerDocumentMembers(asIScriptEngine *engine, const std::string& script_typename);

	//! Rocket#Core#ElementDocument#Show() wrapper
	RASCOREDLL_API void documentShow_Default(Rocket::Core::ElementDocument *obj);

	//! Wrapper for Element#AppendChild() - removes a reference from 'element' after it is appended (this is neccessary to prevent leaks)
	RASCOREDLL_API void ElemAppendChild(Rocket::Core::Element *element, bool dom_element, Rocket::Core::Element *obj);
	//! Provides default param for Rocket#Core#Element#AppendChild()
	RASCOREDLL_API void ElemAppendChild_default(Rocket::Core::Element *element, Rocket::Core::Element *obj);

	//! Dispatches an event
	RASCOREDLL_API bool ElemDispatchEvent_default(const EMP::Core::String &event, const EMP::Core::Dictionary &parameters, Rocket::Core::Element *obj);

	//! Dispatches an event with an empty dictionary for the parameters
	RASCOREDLL_API bool ElemDispatchEvent_noparams(const EMP::Core::String &event, Rocket::Core::Element *obj);

#include "ras_RegisterElementMembers.inl"

}}}

#endif