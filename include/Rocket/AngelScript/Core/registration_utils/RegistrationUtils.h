/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_REGISTRATIONUTILS
#define H_ROCKET_AS_REGISTRATIONUTILS

#include <angelscript.h>

#include <type_traits>

#include "../Exception.h"
#include "../EventListener.h"
#include "RegisterElement.h"


namespace Rocket { namespace AngelScript {
	//! internal methods which register various methods / types
	namespace _registration_utils {}
}}

namespace Rocket { namespace AngelScript { namespace _registration_utils {

	void buildClassWrapper();

	//! Registers Rocket#Core#String
	void registeString(asIScriptEngine *engine);

	//! Registers members of Rocket#Core#Context
	void registerContextMembers(asIScriptEngine *engine);

	//! Registers ElementDocument#FocusFlags enumeration
	void registerFocusFlagsEnum(asIScriptEngine *engine);

	//! Registers ElementDocument#FocusFlags enumeration
	void registerKeyIdentifierEnum(asIScriptEngine *engine);
	//! Registers ElementDocument#FocusFlags enumeration
	void registerKeyModifierEnum(asIScriptEngine *engine);

	//! Registers members of Rocket#Core#Event
	void registerEventMembers(asIScriptEngine *engine);

	void registerPropertyDictionary(asIScriptEngine *engine);

	//! Registers members of Rocket#Core#EventListener interface
	//void registerEventListenerMembers(asIScriptEngine *engine);

	//! Type registration methods
	namespace registerType {
		//! Register a type that derives from Rocket#Core#ReferenceCountable
		template <typename T>
		inline void referenceCountable(asIScriptEngine *engine, const std::string &script_name);

		//! Registers an interface typename
		inline void interface(asIScriptEngine *engine, const std::string &script_name);

#include "RegisterType.inl"
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
	//static Rocket::Core::StringBase<T>::size_type FindFirstNotOf(const Rocket::Core::StringBase<T> &str, const Rocket::Core::StringBase<T> &chars)
	//{
	//	typedef Rocket::Core::StringBase<T> StringT;

	//	for (int i = 0; i < str.Length(); i++)
	//	{
	//		if (str
	//	}
	//}

	//template <typename T>
	//static void trim(Rocket::Core::StringBase<T> &str)
	//{
	//	typedef Rocket::Core::StringBase<T> StringT;

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
