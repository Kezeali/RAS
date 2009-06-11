
// Test

#include <Rocket/Core.h>
#include <Rocket/Controls.h>
#include <Rocket/Debugger.h>
#include <Input.h>
#include <Shell.h>

#include <angelscript.h>

#include <ras_Core.h>
#include <ras_ElementInstancer.h>
#include <ras_EventListenerInstancer.h>
//#include <ras_EventListener.h>

#include <ras_Controls.h>

#include <scripts/ScriptElements.h>

#include <Calling/Caller.h>
#include <boost/bind.hpp>

#include "scriptstdstring.h"
#include "scriptbuilder.h"

#include "Callbacks.h"
#include <stdio.h>
#ifdef WIN32
#include <io.h>
#endif


int AddScriptFile(asIScriptModule *module, const std::string &filename)
{
	// Open the script file
	FILE *f = fopen(filename.c_str(), "rb");
	if(f == NULL)
	{
		return -1;
	}
	
#ifdef WIN32
	int len = _filelength(_fileno(f));
#else
	// Determine size of the file
	fseek(f, 0, SEEK_END);
	int len = ftell(f);
	fseek(f, 0, SEEK_SET);
#endif

	// Read the entire file
	std::string code;
	code.resize(len);
	size_t c = fread(&code[0], len, 1, f);

	fclose(f);

	return module->AddScriptSection(filename.c_str(), code.c_str(), code.length());
}

Rocket::Core::Context* context = NULL;

void GameLoop()
{
	glClear(GL_COLOR_BUFFER_BIT);

	context->Update();
	context->Render();

	Shell::FlipBuffers();
}

#if defined EMP_PLATFORM_WIN32
#include <windows.h>
int APIENTRY WinMain(HINSTANCE EMP_UNUSED(instance_handle), HINSTANCE EMP_UNUSED(previous_instance_handle), char* EMP_UNUSED(command_line), int EMP_UNUSED(command_show))
#else
int main(int EMP_UNUSED(argc), char** EMP_UNUSED(argv))
#endif
{
	// Generic OS initialisation, creates a window and attaches OpenGL.
	if (!Shell::Initialise("../") ||
		!Shell::OpenWindow("AngelScript Test", true))
	{
		Shell::Shutdown();
		return -1;
	}

	// Rocket initialisation.
	ShellRenderInterfaceOpenGL opengl_renderer;
	Rocket::Core::SetRenderInterface(&opengl_renderer);

	ShellSystemInterface system_interface;
	Rocket::Core::SetSystemInterface(&system_interface);

	Rocket::Core::Initialise();
	Rocket::Controls::Initialise();

	asIScriptEngine *engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
	RegisterStdString(engine);
	Rocket::AngelScript::RegisterCore(engine);
	Rocket::AngelScript::RegisterStringConversion(engine, "string");

	Rocket::AngelScript::RegisterElementInstancer(engine);

	// Explicit cast - Element@ to ScriptElement@
	Rocket::AngelScript::RegisterScriptElementConversion(engine);

	Rocket::AngelScript::Controls::RegisterControls(engine);

	CBufferedOutStream out;
	engine->SetMessageCallback(asMETHOD(CBufferedOutStream,Callback), &out, asCALL_THISCALL);

	int r;

	asIScriptModule *mod = engine->GetModule("main", asGM_ALWAYS_CREATE);

	r = Rocket::AngelScript::AddElementsScriptSection(engine, "main");
	EMP_ASSERT(r >= 0);

	//CScriptBuilder builder;
	//r = builder.BuildScriptFromFile(engine, "main", "scripts/main.as");
	r = AddScriptFile(mod, "scripts/main.as");
	EMP_ASSERT(r >= 0);

	Rocket::Core::Factory::RegisterEventListenerInstancer(
		new Rocket::AngelScript::InlineEventListenerInstancer(engine, "main")
		);

	r = mod->Build();
	if( r < 0 )
	{
		std::cerr << out.buffer << std::endl;
		printf("Failed to compile the script\n");

		return -1;
	}

	//asIScriptContext *ctx = engine->CreateContext();
	//int fnId = mod->GetFunctionIdByDecl("Context@ Init()");
	//r = ctx->Prepare(fnId);

	using namespace ScriptUtils::Calling;

	LineDebugger ldb;
	//ctx->SetLineCallback(asMETHOD(LineDebugger,Callback), &ldb, asCALL_THISCALL);

	//r = ctx->Execute();
	try
	{
		Caller callInit(mod, "Context@ Init()");
		// Set up exception handling
		ldb.ConnectToCaller(callInit);
		callInit.SetThrowOnException(true);

		context = *static_cast<Rocket::Core::Context**>( callInit() );
		context->AddReference();
	}
	catch (ScriptUtils::Exception)
	{
	}

	//if (r != asEXECUTION_FINISHED)
	if (context == NULL)
	{
		return -1;
	}

	//context = (Rocket::Core::Context*)ctx->GetReturnObject();

	//ctx->Release();
	//ctx = 0;
	//// Create the main Rocket context and set it on the shell's input layer.
	//context = Rocket::Core::CreateContext("main", EMP::Core::Vector2i(1024, 768));
	//if (context == NULL)
	//{
	//	Rocket::Core::Shutdown();
	//	Shell::Shutdown();
	//	return -1;
	//}

	Rocket::Debugger::Initialise(context);
	Input::SetContext(context);

	Shell::LoadFonts("assets/");

	//ctx = engine->CreateContext();
	//fnId = mod->GetFunctionIdByDecl("Document@ LoadDoc()");
	//r = ctx->Prepare(fnId);

	engine->ClearMessageCallback();
	ShellPrint shellOut;
	engine->SetMessageCallback(asMETHOD(ShellPrint,Callback), &shellOut, asCALL_THISCALL);


	try
	{
		Caller callLoadDoc(mod, "Document@ LoadDoc()");
		ldb.ConnectToCaller(callLoadDoc);
		callLoadDoc();
	}
	catch (ScriptUtils::Exception &ex)
	{
		std::cout << ex.GetMessage() << std::endl;
		Shell::Log(ex.GetMessage().c_str());
	}

	//r = ctx->Execute();
	//if (r != asEXECUTION_FINISHED)

	//ctx->Release();


	// Load and show the demo document.
	//Rocket::Core::ElementDocument* document = context->LoadDocument("assets/demo.rml");
	//if (document != NULL)
	//{
	//	document->Show();
	//	document->RemoveReference();
	//}
	//Rocket::Core::ElementDocument * document = context->GetDocument("demo_doc");
	//if (document != NULL)
	//{
	//	context->UnloadDocument(document);
	//}

	Shell::EventLoop(GameLoop);

	// Shutdown Rocket.
	context->RemoveReference();
	Rocket::Core::Shutdown();

	engine->Release();

	Shell::CloseWindow();
	Shell::Shutdown();

	return 0;
}
