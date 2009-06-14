/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_REGISTRATIONUTILS
#define H_ROCKET_AS_REGISTRATIONUTILS

#include <Rocket/Core.h>
#include <angelscript.h>

#include <string>
#include <boost/mpl/assert.hpp>
#include <type_traits>

#include "../ras_Exception.h"
#include "ras_AngelScriptPrimativeTypes.h"
#include "../ras_EventListener.h"


#define C_STR(str) \
	std::string(str).c_str()

namespace Rocket { namespace AngelScript {
	//! internal methods which register various methods / types
	namespace _registration_utils {}
}}

namespace Rocket { namespace AngelScript { namespace _registration_utils {

	void buildClassWrapper();

	//! Registers Rocket#Core#String
	void registerRString(asIScriptEngine *engine);
	//! Registers EMP#Core#String
	void registerEString(asIScriptEngine *engine);

	//! Registers members of Rocket#Core#Context
	void registerContextMembers(asIScriptEngine *engine);

	//! Registers ElementDocument#FocusFlags enumeration
	void registerFocusFlagsEnum(asIScriptEngine *engine, const std::string& script_typename);

	//! Registers members of Rocket#Core#Event
	void registerEventMembers(asIScriptEngine *engine);

	void registerPropertyDictionary(asIScriptEngine *engine);

	//! Registers members of Rocket#Core#EventListener interface
	//void registerEventListenerMembers(asIScriptEngine *engine);

	//! Registers members of Rocket#Core#Element
	template<class T>
	void registerElementMembers(asIScriptEngine *engine, const std::string& script_typename);
	//! Registers members of Rocket#Core#ElementDocument
	template<class T>
	void registerDocumentMembers(asIScriptEngine *engine, const std::string& script_typename);

	//! Rocket#Core#ElementDocument#Show() wrapper
	void documentShow_Default(Rocket::Core::ElementDocument *obj);

	//! Wrapper for Element#AppendChild() - removes a reference from 'element' after it is appended (this is neccessary to prevent leaks)
	void ElemAppendChild(Rocket::Core::Element *element, bool dom_element, Rocket::Core::Element *obj);
	//! Provides default param for Rocket#Core#Element#AppendChild()
	void ElemAppendChild_default(Rocket::Core::Element *element, Rocket::Core::Element *obj);

	//! Dispatches an event
	bool ElemDispatchEvent_default(const EMP::Core::String &event, const EMP::Core::Dictionary &parameters, Rocket::Core::Element *obj);

	//! Dispatches an event with an empty dictionary for the parameters
	bool ElemDispatchEvent_noparams(const EMP::Core::String &event, Rocket::Core::Element *obj);

#include "ras_RegisterElementMembers.inl"

	//! Type registration methods
	namespace registerType {
		//! Register a type that derives from EMP#Core#ReferenceCountable
		template <typename T>
		static void referenceCountable(asIScriptEngine *engine, const std::string &script_name);

		//! Registers an interface (abstract) type
		template <typename T>
		static void interface(asIScriptEngine *engine, const std::string &script_name);

#include "ras_RegisterType.inl"
	};

}}}

	//static std::string trim_copy(const std::string &str)
	//{
	//	std::string::size_type first_char = str.find_first_not_of(" \r\n\t");
	//	std::string::size_type last_char = str.find_last_not_of(" \r\n\t");
	//	if (first_char == std::string::npos)
	//		return std::string();
	//	if (last_char == std::string::npos)
	//		return std::string();
	//	return str.substr(first_char, last_char - first_char + 1);
	//}

	//static void trim(std::string &str)
	//{
	//	std::string::size_type first_char = str.find_first_not_of(" \r\n\t");
	//	if (first_char == std::string::npos)
	//	{
	//		str.clear();
	//		return;
	//	}
	//	else
	//		str.erase(0, first_char);

	//	std::string::size_type last_char = str.find_last_not_of(" \r\n\t");
	//	if (last_char == std::string::npos)
	//	{
	//		str.clear();
	//		return;
	//	}
	//	else
	//		str.erase(last_char+1);
	//}

	//template <typename T>
	//static EMP::Core::StringBase<T>::size_type FindFirstNotOf(const EMP::Core::StringBase<T> &str, const EMP::Core::StringBase<T> &chars)
	//{
	//	typedef EMP::Core::StringBase<T> StringT;

	//	for (int i = 0; i < str.Length(); i++)
	//	{
	//		if (str
	//	}
	//}

	//template <typename T>
	//static void trim(EMP::Core::StringBase<T> &str)
	//{
	//	typedef EMP::Core::StringBase<T> StringT;

	//	StringT::size_type first_char = FindFirstNotOf(str, " \r\n\t");
	//	if (first_char == StringT::npos)
	//	{
	//		str.clear();
	//		return;
	//	}
	//	else
	//		str.erase(0, first_char);

	//	std::string::size_type last_char = str.find_last_not_of(" \r\n\t");
	//	if (last_char == std::string::npos)
	//	{
	//		str.clear();
	//		return;
	//	}
	//	else
	//		str.erase(last_char+1);
	//}

#endif
