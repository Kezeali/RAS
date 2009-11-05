/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_ELEMENTDOCUMENT
#define H_ROCKET_AS_ELEMENTDOCUMENT

#include "ras_Config.h"

#include <Rocket/Core/ElementDocument.h>
#include <Rocket/Core/ElementInstancer.h>

#include <angelscript.h>


namespace Rocket { namespace AngelScript {

	//! ElementDocument with LoadScript implementation for AngelScript
	class ElementScriptableDocument : public Rocket::Core::ElementDocument
	{
	public:
		ElementScriptableDocument(asIScriptEngine *engine, const EMP::Core::String &tag);
		virtual ~ElementScriptableDocument();

		//! Load an AS script into the document.
		/// @param[in] stream Stream of code to process.
		/// @param[in] source_name Name of the the script the source comes from, useful for debug information.
		virtual void LoadScript(EMP::Core::Stream* stream, const EMP::Core::String& source_name);

		//! Checks for the 'load' event, which is when the script module will be built
		virtual void ProcessEvent(Rocket::Core::Event& event);

	protected:
		asIScriptEngine *m_Engine;

		typedef EMP::Core::STL::set<EMP::Core::String> ModuleNameSet;
		ModuleNameSet m_ModuleNames;
	};

	/*!
	*	Passes an AS engine pointer to new ScriptableDocument objects.
	*
	* ScriptableDocuments require access to an AS engine so that they can
	* create and build modules for embedded code - i.e. this allows support
	* for the <script> tag.
	*/
	class ScriptableDocumentInstancer : public Rocket::Core::ElementInstancer
	{
	public:
		ScriptableDocumentInstancer(asIScriptEngine* engine);
		virtual ~ScriptableDocumentInstancer();

		/// Release the instancer
		virtual void Release();

		/// Instances an element given the tag name and attributes
		/// @param tag Name of the element to instance
		/// @param attributes vector of name value pairs
		virtual Core::Element* InstanceElement(Core::Element* parent, const EMP::Core::String& tag, const EMP::Core::XMLAttributes& attributes);

		/// Releases the given element
		/// @param element to release
		virtual void ReleaseElement(Rocket::Core::Element* element);

	protected:
		asIScriptEngine *m_Engine;
		const char *m_DefaultModuleName;
	};

	RASCOREDLL_API void RegisterScriptableDocumentInstancer(asIScriptEngine *engine);

}}

#endif