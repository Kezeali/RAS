/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_EXCEPTION
#define H_ROCKET_AS_EXCEPTION

#include <string>

namespace Rocket { namespace AngelScript {

	class Exception
	{
	public:
		Exception(const std::string &message)
			: m_Message(message)
		{}

	public:
		const std::string &GetMessage() const { return m_Message; }

		std::string m_Message;
	};

}}

#endif
