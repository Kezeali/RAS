/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../include/Rocket/AngelScript/Core/ras_ElementDocument.h"

#include <EMP/Core/String.h>
#include <EMP/Core/Stream.h>
#include <Rocket/Core/Event.h>
#include <Rocket/Core/Factory.h>

#include <sstream>


namespace Rocket { namespace AngelScript {

	ElementScriptableDocument::ElementScriptableDocument(asIScriptEngine *engine, const EMP::Core::String &tag)
		: m_Engine(engine),
		Rocket::Core::ElementDocument(tag)
	{
	}

	ElementScriptableDocument::~ElementScriptableDocument()
	{
	}

	void ElementScriptableDocument::LoadScript(EMP::Core::Stream* stream, const EMP::Core::String& source_name)
	{ 
		EMP::Core::String moduleName = GetAttribute("module", GetTitle());
		EMP::Core::String sectionName = source_name;
		if (sectionName.Empty())
		{
			static unsigned int next = 0;
			std::ostringstream ser;
			ser << next++;
			sectionName = ser.str().c_str();
		}
		asIScriptModule *module = NULL;

		// If this is a new module name, make sure the module doesn't already exist (that
		//  would indicate that it was created by something other than this document, and
		//  in that case may or may not be Built already)
		if (m_ModuleNames.find(moduleName) == m_ModuleNames.end())
		{
			module = m_Engine->GetModule(moduleName.CString(), asGM_ONLY_IF_EXISTS);
			EMP_ASSERTMSG(module == NULL, "<script> elements must use modules unique to the documents they reside in");
			if (module != NULL)
				return;
		}

		module = m_Engine->GetModule(moduleName.CString(), asGM_CREATE_IF_NOT_EXISTS);
		if (module == NULL)
			return;

		m_ModuleNames.insert(moduleName);

		size_t source_length = stream->Length();
		EMP::Core::String code;
		stream->Read(code, source_length);

		module->AddScriptSection(sectionName.CString(), code.CString(), source_length);
	}

//#define RAS_DOCUMENT__USE_PROPERTIES_OBJECT

#ifdef RAS_DOCUMENT__USE_PROPERTIES_OBJECT
	static const char *s_ModulePropertiesScript =
		"class ModuleProperties {\n"
		"Document@ document;\n"
		"}\n"
		"ModuleProperties module;";

	static const size_t s_ModulePropertiesScriptLength = 71;
#endif

	void ElementScriptableDocument::ProcessEvent(Rocket::Core::Event& e)
	{
		Rocket::Core::ElementDocument::ProcessEvent(e);

		if (e.GetType() == "load")
		{
			for (ModuleNameSet::iterator it = m_ModuleNames.begin(), end = m_ModuleNames.end(); it != end; ++it)
			{
				asIScriptModule *module = m_Engine->GetModule(it->CString());
				if (module != NULL)
				{
					int r;
#ifdef RAS_DOCUMENT__USE_PROPERTIES_OBJECT
					r = module->AddScriptSection("module_properties", s_ModulePropertiesScript, s_ModulePropertiesScriptLength);
#else
					r = module->AddScriptSection("module_properties", "Document@ module_document;", 26);
#endif
					r = module->Build();
					EMP_ASSERTMSG(r >= 0, "Failed to build <script> module");
					if (r >= 0)
					{
#ifdef RAS_DOCUMENT__USE_PROPERTIES_OBJECT
						r = module->GetGlobalVarIndexByDecl("ModuleProperties module");
						void* var = module->GetAddressOfGlobalVar(r);
						asIScriptObject *moduleProperties = (asIScriptObject*)var;
						void* prop = moduleProperties->GetPropertyPointer(0);
#else
						r = module->GetGlobalVarIndexByDecl("Document@ module_document");
						void* prop = module->GetAddressOfGlobalVar(r);
#endif
						*((ElementDocument**)prop) = this;
					}
				}
			}
		}
	}

	// ScriptableDocumentInstancer impl. follows
	ScriptableDocumentInstancer::ScriptableDocumentInstancer(asIScriptEngine *engine)
		: m_Engine(engine)
	{}

	ScriptableDocumentInstancer::~ScriptableDocumentInstancer()
	{}

	void ScriptableDocumentInstancer::Release()
	{
		delete this;
	}

	Core::Element* ScriptableDocumentInstancer::InstanceElement(Core::Element* parent, const EMP::Core::String& tag, const EMP::Core::XMLAttributes& attributes)
	{
		return new ElementScriptableDocument(m_Engine, tag);
	}

	void ScriptableDocumentInstancer::ReleaseElement(Rocket::Core::Element* element)
	{
	}

	RASCOREDLL_API void RegisterScriptableDocumentInstancer(asIScriptEngine *engine)
	{
		Rocket::Core::Factory::RegisterElementInstancer("body", new Rocket::AngelScript::ScriptableDocumentInstancer(engine))
			->RemoveReference();
	}

}}
