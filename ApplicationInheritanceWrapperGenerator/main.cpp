#include <Rocket/Core.h>
#include <Rocket/Debugger.h>
#include <Input.h>
#include <Shell.h>

#include <angelscript.h>

#include <fstream>

#include <Rocket/AngelScript/Core/ras_Core.h>
//#include <Rocket/AngelScript/Core/ras_ElementWrapper.h>

#include <Inheritance/ProxyGenerator.h>
#include <Inheritance/CompleteHeaderGenerator.h>
#include "../Test/scriptstdstring.h"

#include "../Test/Callbacks.h"


int main(int argc, char** argv)
{
	asIScriptEngine *engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
	RegisterStdString(engine);
	// Core functionality
	Rocket::AngelScript::RegisterCore(engine);
	Rocket::AngelScript::RegisterStringConversion(engine, "string");
	
	// Script Element bindings (application side - the script side stuff is generated below!)
	//Rocket::AngelScript::RegisterElementInterface(engine);

	COutStream out;
	engine->SetMessageCallback(asMETHOD(COutStream,Callback), &out, asCALL_THISCALL);

	using namespace ScriptUtils::Inheritance;

	std::cout << "Generating ScriptElement types" << std::endl;
	CompleteHeaderGenerator hgen("../scripts/ScriptElement.h",
		"Elements",
		"<angelscript.h>", "Rocket,AngelScript");
	hgen.Generate(engine, "Element", NULL, "IElement");

	return 0;
}