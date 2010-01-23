// Classes which provide callback functions for asIScriptEngine, etc.

#ifndef H_RAS_TEST_CALLBACKS
#define H_RAS_TEST_CALLBACKS

#include <Rocket/Core.h>
#include <iostream>
#include <sstream>

#include <ScriptUtils/Calling/Caller.h>
#include <boost/bind.hpp>


class COutStream
{
public:
	void Callback(asSMessageInfo *msg) 
	{ 
		const char *msgType = 0;
		if( msg->type == 0 ) msgType = "Error  ";
		if( msg->type == 1 ) msgType = "Warning";
		if( msg->type == 2 ) msgType = "Info   ";

		printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, msgType, msg->message);
	}
};

class CBufferedOutStream
{
public:
	void Callback(asSMessageInfo *msg) 
	{ 
		const char *msgType = 0;
		if( msg->type == 0 ) msgType = "Error  ";
		if( msg->type == 1 ) msgType = "Warning";
		if( msg->type == 2 ) msgType = "Info   ";

		char buf[256];
#ifdef _MSC_VER
#if _MSC_VER >= 1500
		_snprintf_s(buf, 255, 255, "%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, msgType, msg->message);
#else
		_snprintf(buf, 255, "%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, msgType, msg->message);
#endif
#else
		snprintf(buf, 255, "%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, msgType, msg->message);
#endif
		buf[255] = '\0';

		buffer += buf;
	}

	std::string buffer;
};

class ShellPrint
{
public:
	void Callback(asSMessageInfo *msg) 
	{ 
		const char *msgType = 0;
		if( msg->type == 0 ) msgType = "Error  ";
		if( msg->type == 1 ) msgType = "Warning";
		if( msg->type == 2 ) msgType = "Info   ";

		Shell::Log("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, msgType, msg->message);
		Rocket::Core::Log::Message(EMP::Core::Log::LT_WARNING, "%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, msgType, msg->message);
	}
};

class LineDebugger
{
public:
	std::string buffer;

	boost::signals2::scoped_connection m_LineConn;
	boost::signals2::scoped_connection m_ExceptionConn;

	void ConnectToCaller(ScriptUtils::Calling::Caller &caller)
	{
		m_LineConn = caller.ConnectLineCallback( boost::bind(&LineDebugger::Callback, this, _1) );
		m_ExceptionConn = caller.ConnectExceptionCallback( boost::bind(&LineDebugger::ExceptionCallback, this, _1) );
	}

	void Callback(asIScriptContext *ctx)
	{
		asIScriptEngine *eng = ctx->GetEngine();

		int fnId = ctx->GetCurrentFunction();
		int column, line = ctx->GetCurrentLineNumber(&column);

		asIScriptFunction *fn = eng->GetFunctionDescriptorById(fnId);

		std::stringstream strstr;
		strstr << "----";
		strstr << fn->GetName() << " (" << line << "," << column << ")" << std::endl;

		int vars = ctx->GetVarCount();
		for (int i = 0; i < vars; i++)
		{
			strstr << ctx->GetVarDeclaration(i) << ": ";
			printVar(strstr, ctx, i);
			strstr << std::endl;
		}
		strstr << "----" << std::endl;

		std::string res = strstr.str();
		buffer += res;
		std::cout << res;
		//Shell::Log(res.c_str());
	}

	void ExceptionCallback(asIScriptContext *ctx)
	{
		asIScriptEngine *engine = ctx->GetEngine();

		std::stringstream desc;
		desc << "Script Exception: " << ctx->GetExceptionString() << std::endl;

		int funcId = ctx->GetExceptionFunction();
		const asIScriptFunction *function = engine->GetFunctionDescriptorById(funcId);
		desc << "  in function: " << function->GetDeclaration() << " (line " << ctx->GetExceptionLineNumber() << ")" << std::endl;
		desc << "    in module: " << function->GetModuleName() << std::endl;
		desc << "   in section: " << function->GetScriptSectionName();

		desc << "Call Trace:\n";
		printCallstack(engine, ctx, desc);

		buffer += desc.str();
		std::cout << desc;
		Shell::DisplayError(desc.str().c_str());
	}

	static const size_t maxPregenSpaces = 0;
	/*static const char * spaces[maxPregenSpaces+1] = {
		"", " ", "  ", "   ", "    ", "     ", "      ", "       ",
		"        ", "         ", "          ", "           ", "            ",
		NULL
	};*/

	static void printCallstack(asIScriptEngine *const engine, asIScriptContext *const ctx, std::ostream &str)
	{
		//std::stringstream str;
		for (int i = ctx->GetCallstackSize(); i > 0; i++)
		{
			if (i < maxPregenSpaces)
			{
				//str << spaces[i];
			}
			else
			{
				//str << spaces[maxPregenSpaces-1];
				for (int k = maxPregenSpaces; k < i ; ++k)
					str << " ";
			}

			int fnId = ctx->GetCallstackFunction(i);
			if (fnId < 0)
			{
				str << std::endl;
				continue;
			}
			const asIScriptFunction *fn = engine->GetFunctionDescriptorById(fnId);
			std::string sig = fn->GetDeclaration(true);
			int line, column;
			line = ctx->GetCallstackLineNumber(i, &column);

			str << "+ " << sig << " (" << line << "," << column << ")\n";
		}

		//return str.str();
	}

	void printVar(std::ostream &strstr, asIScriptContext *ctx, int var_ind)
	{
		asIScriptEngine *eng = ctx->GetEngine();
		void *varPtr = ctx->GetAddressOfVar(var_ind);
		int typeId = ctx->GetVarTypeId(var_ind);

		if (typeId == eng->GetTypeIdByDecl("int"))
		{
			strstr << *(int*)varPtr;
		}
		else if (typeId == eng->GetTypeIdByDecl("uint"))
		{
			strstr << *(unsigned int*)varPtr;
		}
		else if (typeId == eng->GetTypeIdByDecl("int8"))
		{
			strstr << *(char*)varPtr;
		}
		else if (typeId == eng->GetTypeIdByDecl("uint8"))
		{
			strstr << *(unsigned char*)varPtr;
		}
		else if (typeId == eng->GetTypeIdByDecl("string"))
		{
			std::string *str = (std::string*)varPtr;
			if (str)
			{
				strstr << *str;
			}
			else
			{
				strstr << "NULL";
			}
		}
		else if (typeId == eng->GetTypeIdByDecl("r_String"))
		{
			Rocket::Core::String *str = (Rocket::Core::String*)varPtr;
			if (str)
			{
				strstr << str->CString();
			}
			else
			{
				strstr << "NULL";
			}
		}
		else if (typeId == eng->GetTypeIdByDecl("e_String"))
		{
			EMP::Core::String *str = (EMP::Core::String*)varPtr;
			if (str)
			{
				strstr << str->CString();
			}
			else
			{
				strstr << "NULL";
			}
		}
		else if (typeId == eng->GetTypeIdByDecl("e_Vector2i"))
		{
			EMP::Core::Vector2i *vec = (EMP::Core::Vector2i*)varPtr;
			if (vec)
			{
				strstr << vec->x << "," << vec->y;
			}
			else
			{
				strstr << "NULL";
			}
		}
		else
		{
			strstr << "<unknown type>";
		}
	}
};

#endif
