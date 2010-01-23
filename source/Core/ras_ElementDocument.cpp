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

//#define RAS_DOCUMENT__USE_PROPERTIES_OBJECT


namespace Rocket { namespace AngelScript {

	ElementScriptableDocument::ElementScriptableDocument(asIScriptEngine *engine, const EMP::Core::String &tag)
		: m_Engine(engine),
		Rocket::Core::ElementDocument(tag)
	{
	}

	ElementScriptableDocument::~ElementScriptableDocument()
	{
		asIScriptModule *module = m_Engine->GetModule(m_ModuleName.CString());
		if (module != NULL)
		{
			int varInd;
#ifdef RAS_DOCUMENT__USE_PROPERTIES_OBJECT
			varInd = module->GetGlobalVarIndexByDecl("ModuleProperties module");
			void* var = module->GetAddressOfGlobalVar(varInd);
			asIScriptObject *moduleProperties = (asIScriptObject*)var;
			void* prop = moduleProperties->GetPropertyPointer(0);
#else
			varInd = module->GetGlobalVarIndexByDecl("Document@ module_document");
			void* prop = module->GetAddressOfGlobalVar(varInd);
#endif
			if (prop != NULL)
				*((ElementDocument**)prop) = NULL;
		}
		m_Engine->DiscardModule(m_ModuleName.CString());
	}

	inline bool readModuleName(EMP::Core::Stream* stream, EMP::Core::String &code, EMP::Core::String &out)
	{
		if (stream->Read(code, 9) == 9 && code == "#module \"") // 9 = strlen("#module \"")
		{
			code.Clear(); // remove the #module directive from the code

			bool ok = true;
			// Keep reading till the end of the module name is found
			do
			{
				if (stream->Read(out, 1) == 0)
				{
					ok = false; // the end of the stream was found before the end of the module name
					break;
				}
			} while (out[out.Length()-1] != '\"');

			if (ok)
				out.Resize(out.Length()-1); // Remove the trailing quotation mark
			else
				return false;
			return true;
		}
		else
			return false;
	}

	void ElementScriptableDocument::LoadScript(EMP::Core::Stream* stream, const EMP::Core::String& source_name)
	{
		ScriptSection section;

		section.name = source_name;
		if (section.name.Empty())
		{
			static unsigned int next = 0;
			std::ostringstream ser;
			ser << "inline_section_";
			ser << next++;
			section.name = ser.str().c_str();
		}

		if (m_ModuleName.Empty())
		{
			m_ModuleName = GetSourceURL();
			if (m_ModuleName.Empty())
			{
				EMP_ERRORMSG("Couldn't create document module for a scriptable document - couldn't get the source URL.");
				return;
			}
			if (m_Engine->GetModule(m_ModuleName.CString()) != NULL)
			{
				EMP_ERRORMSG(("Couldn't create document module for " + m_ModuleName + " - a module with the required name already exists.").CString());
				return;
			}
		}
		
		//EMP::Core::String moduleName;
		//// Check for non-default module name
		//if (!readModuleName(stream, section.code, moduleName))
		//	moduleName = m_ModuleName; // Use the filename
		//else
		//{
		//	asIScriptModule *module = NULL;
		//	module = m_Engine->GetModule(moduleName.CString());
		//	if (module != NULL)
		//		return;
		//}

		size_t source_length = stream->Length();
		stream->Read(section.code, source_length);

		m_Sections.push_back(section);
		Build();
	}

#ifdef RAS_DOCUMENT_USE_PROPERTIES_OBJECT
	static const char *s_ModulePropertiesScript =
		"class ModuleProperties {\n"
		"Document@ document;\n"
		"}\n"
		"ModuleProperties module;";

	static const size_t s_ModulePropertiesScriptLength = 71;
#endif

	void ElementScriptableDocument::Build()
	{
		asIScriptModule *module = m_Engine->GetModule(m_ModuleName.CString(), asGM_CREATE_IF_NOT_EXISTS);
		if (module == NULL)
		{
			EMP_ERRORMSG(("Couldn't create document module for " + m_ModuleName).CString());
			return;
		}

		int r;
		// Add all the script sections 
		for (SectionList::iterator it = m_Sections.begin(), end = m_Sections.end(); it != end; ++it)
		{
			r = module->AddScriptSection(it->name.CString(), it->code.CString(), it->code.Length());
			EMP_ASSERTMSG(r >= 0, ("Adding script section '" + it->name + "' to module '" + m_ModuleName + "' failed").CString());
		}

		// Add the module property
#ifdef RAS_DOCUMENT_USE_PROPERTIES_OBJECT
		r = module->AddScriptSection("module_properties", s_ModulePropertiesScript, s_ModulePropertiesScriptLength);
#else
		r = module->AddScriptSection("module_properties", "Document@ module_document;", 26);
#endif
		r = module->Build();
		EMP_ASSERTMSG(r >= 0, "Failed to build document module");
		// Set the value of the module-property document pointer
		if (r >= 0)
		{
#ifdef RAS_DOCUMENT_USE_PROPERTIES_OBJECT
			r = module->GetGlobalVarIndexByDecl("ModuleProperties module");
			void* var = module->GetAddressOfGlobalVar(r);
			asIScriptObject *moduleProperties = (asIScriptObject*)var;
			void* prop = moduleProperties->GetPropertyPointer(0);
#else
			r = module->GetGlobalVarIndexByDecl("Document@ module_document");
			void* prop = module->GetAddressOfGlobalVar(r);
#endif
			if (prop != NULL)
				*((ElementDocument**)prop) = this;
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
		delete element;
	}

	RASCOREDLL_API void RegisterScriptableDocumentInstancer(asIScriptEngine *engine)
	{
		Rocket::Core::Factory::RegisterElementInstancer("body", new Rocket::AngelScript::ScriptableDocumentInstancer(engine))
			->RemoveReference();
	}

}}
