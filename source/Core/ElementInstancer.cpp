/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../../include/Rocket/AngelScript/Core/ElementInstancer.h"

#include "../../include/Rocket/AngelScript/Core/ElementWrapper.h"

#include <ScriptUtils/Calling/Caller.h>
#include <ScriptUtils/Inheritance/TypeTraits.h>


namespace Rocket { namespace AngelScript {

	/*!
	*	AS Element Instancer
	*
	* \todo
	* Another ElementInstancer class that calls a factory fn. taking tag & xmlAttributes strings as arguments
	*/
	template <class _Element>
	class ElementInstancer : public Rocket::Core::ElementInstancer
	{
	public:
		ElementInstancer(asIScriptEngine* engine, int typeId);
		virtual ~ElementInstancer();

		/// Release the instancer
		virtual void Release();

		/// Instances an element given the tag name and attributes
		/// @param tag Name of the element to instance
		/// @param attributes vector of name value pairs
		virtual Core::Element* InstanceElement(Core::Element* parent, const Rocket::Core::String& tag, const Rocket::Core::XMLAttributes& attributes);

		/// Releases the given element
		/// @param element to release
		virtual void ReleaseElement(Rocket::Core::Element* element);

	protected:
		asIScriptEngine *m_Engine;

	private:
		asIObjectType* m_Type;
		int m_TypeId;
	};

	template<class ElementT>
	ElementInstancer<ElementT>::ElementInstancer(asIScriptEngine *engine, int typeId)
		: m_Engine(engine), m_TypeId(typeId)
	{
	}

	template<class ElementT>
	ElementInstancer<ElementT>::~ElementInstancer()
	{}

	template<class ElementT>
	void ElementInstancer<ElementT>::Release()
	{
		delete this;
	}

	template <class ElementT>
	Core::Element* ElementInstancer<ElementT>::InstanceElement(Core::Element* ROCKET_UNUSED(parent), const Rocket::Core::String& tag, const Rocket::Core::XMLAttributes& attributes)
	{
		ElementWrapper<ElementT> *elementWrapper = new ElementWrapper<ElementT>(tag.CString());

		asIObjectType *type = m_Engine->GetObjectTypeById(m_TypeId);
		//std::string type_name(type->GetName());

		//int factoryId = type->GetFactoryIdByDecl((type_name+"@ "+type_name+"(Rocket::Element@)");
		ScriptUtils::Calling::Caller callCtor = ScriptUtils::Calling::Caller::FactoryCaller(type, "Rocket::Element@");
		callCtor.SetThrowOnException(true);

		asIScriptObject *obj = NULL;
		try
		{
			elementWrapper->AddReference();
			obj = *static_cast<asIScriptObject**>( callCtor(elementWrapper) );
		}
		catch (ScriptUtils::Exception) {
			return NULL;
		}
		if (obj == NULL)
			return NULL;

		m_Engine->NotifyGarbageCollectorOfNewObject(elementWrapper, m_Engine->GetObjectTypeById(ElementWrapper<ElementT>::TypeId));

		elementWrapper->SetScriptObject( obj );
		//obj->Release();

		return dynamic_cast<Core::Element*>( elementWrapper );
	}

	template <class ElementT>
	void ElementInstancer<ElementT>::ReleaseElement(Rocket::Core::Element* element)
	{
		// Delete the wrapper
		//ElementWrapper<ElementT> *elementWrapper = dynamic_cast<ElementWrapper<ElementT>*>( element );
		//ROCKET_ASSERT(elementWrapper);
		//delete elementWrapper;
	}

	template <class ElementT>
	class FactoryElementInstancer : public Rocket::Core::ElementInstancer
	{
	public:
		FactoryElementInstancer(asIScriptEngine* engine, const char * module, const std::string &decl);
		virtual ~FactoryElementInstancer();

		/// Release the instancer
		virtual void Release();

		/// Instances an element given the tag name and attributes
		/// @param tag Name of the element to instance
		/// @param attributes vector of name value pairs
		virtual Core::Element* InstanceElement(Core::Element* parent, const Rocket::Core::String& tag, const Rocket::Core::XMLAttributes& attributes);

		/// Releases the given element
		/// @param element to release
		virtual void ReleaseElement(Rocket::Core::Element* element);

	protected:
		asIScriptEngine *m_Engine;

	private:
		const char * m_Module;
		std::string m_Decl;
	};

	template<class ElementT>
	FactoryElementInstancer<ElementT>::FactoryElementInstancer(asIScriptEngine *engine, const char * module, const std::string &decl)
		: m_Engine(engine), m_Module(module), m_Decl(decl)
	{
	}

	template<class ElementT>
	FactoryElementInstancer<ElementT>::~FactoryElementInstancer()
	{}

	template<class ElementT>
	void FactoryElementInstancer<ElementT>::Release()
	{
		delete this;
	}

	template <class ElementT>
	Core::Element* FactoryElementInstancer<ElementT>::InstanceElement(Core::Element* ROCKET_UNUSED(parent), const Rocket::Core::String& tag, const Rocket::Core::XMLAttributes& attributes)
	{
		asIScriptModule *module = m_Engine->GetModule(m_Module);
		if (module == NULL)
			return NULL;

		//Core::Element *element = new ElementT(tag.CString());
		// Create a script calling wrapper (calls script overrides when available)
		//  Note that this is before the script object - since that must be
		//  passed a valid entity on construction
		ElementWrapper<ElementT> *elementWrapper = new ElementWrapper<ElementT>(tag.CString());

		ScriptUtils::Calling::Caller callFactory = ScriptUtils::Calling::Caller::Create(module, m_Decl.c_str());
		callFactory.SetThrowOnException(true);
		asIScriptObject *obj = NULL;
		try
		{
			elementWrapper->AddReference();
			// Create the actual element, passing it the wrapper
			obj = *static_cast<asIScriptObject**>( callFactory(elementWrapper/*, attributes*/) );
		}
		catch (ScriptUtils::Exception)
		{
			return NULL;
		}

		if (obj == NULL)
				return NULL;

		m_Engine->NotifyGarbageCollectorOfNewObject(elementWrapper, obj->GetObjectType());

		// Set the script object for running overrided methods
		elementWrapper->SetScriptObject(obj);
		obj->Release();

		// I guess this is what you are supposed to do with the attributes param...
		elementWrapper->SetAttributes(&attributes);

		return static_cast<Core::Element*>(elementWrapper);
	}

	template <class ElementT>
	void FactoryElementInstancer<ElementT>::ReleaseElement(Rocket::Core::Element* element)
	{
		// Delete the wrapper
		ElementWrapper<ElementT> *elementWrapper = dynamic_cast<ElementWrapper<ElementT>*>( element );
		if (elementWrapper != NULL && elementWrapper->GetScriptObject() != NULL)
		{
			//asIScriptObject *obj = static_cast<asIScriptObject*>( elementWrapper->GetScriptObject() );

			//SC::Caller call_SetAppObject(obj, "void _SetAppObject(Element@)");
			//if ( call_SetAppObject )
			//	call_SetAppObject(NULL);

			delete elementWrapper;
		}
	}


	//! checks whether the given type inherits from ScriptElement
	bool isElementType(asIScriptEngine *engine, int typeId)
	{
		asIObjectType *type = engine->GetObjectTypeById(typeId);

		asIObjectType *baseType = type->GetBaseType();
		while (baseType != NULL)
		{
			if (std::strcmp(baseType->GetName(), "ScriptElement") == 0)
				return true;

			baseType = baseType->GetBaseType();
		}

		return false;
	}

	//! \see getElementType
	enum ElementBaseType
	{
		NONE,
		ELEMENT,
		ELEMENTDOCUMENT,
		ELEMENTTEXT
	};

	//! Returns the most derrived known proxy type that this type derrives from
	ElementBaseType getElementType(asIScriptEngine *engine, int typeId)
	{
		asIObjectType *type = engine->GetObjectTypeById(typeId);

		asIObjectType *baseType = type->GetBaseType();
		while (baseType != NULL)
		{
			if (std::strcmp(baseType->GetName(), "ScriptElement") == 0)
				return ELEMENT;
			if (std::strcmp(baseType->GetName(), "ScriptDocument") == 0)
				return ELEMENTDOCUMENT;

			baseType = baseType->GetBaseType();
		}

		return NONE;
	}

	void BindElementInstancer(const Rocket::Core::String &rml_name, asIScriptEngine *engine, int typeId)
	{
		// Check that the script type inherits from ScriptElement
		//  Only inheriting from ScriptElement is implemented at this point -
		//  I'm not sure if it's worth implementing other element base types
		if ( isElementType(engine, typeId) )
		{
			AngelScript::ElementInstancer<Rocket::Core::Element> *newInstancer =
				new AngelScript::ElementInstancer<Rocket::Core::Element>(engine, typeId);
			Rocket::Core::Factory::RegisterElementInstancer(rml_name, newInstancer);
			newInstancer->RemoveReference();
		}
	}

	void BindElementFactory(const Rocket::Core::String &rml_name,
		asIScriptEngine *engine, const char *module_name, const std::string &decl)
	{
		// Check that the script type inherits from ScriptElement
		//  Only inheriting from ScriptElement is implemented at this point -
		//  I'm not sure if it's worth implementing other element base types
		//if ( isElementType(engine, typeId) )
		{
			AngelScript::FactoryElementInstancer<Rocket::Core::Element> *newInstancer =
				new AngelScript::FactoryElementInstancer<Rocket::Core::Element>(engine, module_name, decl);

			Rocket::Core::Factory::RegisterElementInstancer(rml_name, newInstancer);
			newInstancer->RemoveReference();
		}
	}

	//! To be registered as a script Fn
	/*!
	* \see BindElementInstancer()
	*/
	void BindElementInstancer_Wrapper(const Rocket::Core::String &rml_name, const Rocket::Core::String &decl)
	{
		// This method is intended to be called by a script, so there should be an active context
		//  otherwise, the call is ignored (i.e. no else case)
		asIScriptContext *context = asGetActiveContext();
		if (context != NULL)
		{
			asIScriptEngine *engine = context->GetEngine();

			// Find the module the current function is being executed in
			int fnId = context->GetFunction()->GetId(); ROCKET_ASSERT(fnId);
			const char * moduleName = engine->GetFunctionById(fnId)->GetModuleName();
			asIScriptModule *module = engine->GetModule(moduleName); ROCKET_ASSERT(module != NULL);

			// Find the type with the given declaration in the current module
			int typeId = module->GetTypeIdByDecl(decl.CString());
			if (typeId < 0)
			{
				context->SetException("Type doesn't exist");
				return;
			}

			BindElementInstancer(rml_name, engine, typeId);
		}
	}

	//! To be registered as a script Fn
	/*!
	* \see BindElementFactory()
	*/
	void BindElementFactory_Wrapper(const Rocket::Core::String &rml_name, const Rocket::Core::String &decl)
	{
		// This method is intended to be called by a script, so there should be an active context
		//  otherwise, the call is ignored (i.e. no else case)
		asIScriptContext *context = asGetActiveContext();
		if (context != NULL)
		{
			asIScriptEngine *engine = context->GetEngine();

			// Find the module the current function is being executed in
			int fnId = context->GetFunction()->GetId(); ROCKET_ASSERT(fnId);
			const char * moduleName = engine->GetFunctionById(fnId)->GetModuleName();
			
			// Check that the passed function exists
			asIScriptModule *module = engine->GetModule(moduleName); ROCKET_ASSERT(module != NULL);
			// Find the type with the given declaration in the current module
			asIScriptFunction* func = module->GetFunctionByDecl(decl.CString());
			if (!func)
			{
				context->SetException("Function doesn't exist");
				return;
			}

			BindElementFactory(rml_name, engine, moduleName, decl.CString());
		}
	}

	void RegisterBindElementInstancer(asIScriptEngine *engine)
	{
		int r = engine->RegisterGlobalFunction("void RegisterElementType(const String &in rml_name, const String &in decl)",
			asFUNCTION(BindElementInstancer_Wrapper), asCALL_CDECL);
		ROCKET_ASSERT(r >= 0);

		r = engine->RegisterGlobalFunction("void RegisterElementFactory(const String &in rml_name, const String &in decl)",
			asFUNCTION(BindElementFactory_Wrapper), asCALL_CDECL);
		ROCKET_ASSERT(r >= 0);
	}

	//! Ref-cast-style method for getting ScriptElement objects
	template <class ElementT>
	asIScriptObject * GetScriptObject(ElementT *element)
	{
		ElementWrapper<ElementT> *wrapper = dynamic_cast<ElementWrapper<ElementT>*>( element );
		if (wrapper != NULL && wrapper->GetScriptObject() != NULL)
		{
			asIScriptObject *script_obj = static_cast<asIScriptObject*>( wrapper->GetScriptObject() );
			script_obj->AddRef();
			element->RemoveReference();
			return script_obj;
		}
		else
			return NULL;
	}

	void RegisterScriptElementConversion(asIScriptEngine *engine)
	{
		int r;
		r = engine->RegisterGlobalFunction("IElement@ unwrap(Element@)",
			asFUNCTION(GetScriptObject<Rocket::Core::Element>),
			asCALL_CDECL);
		ROCKET_ASSERT(r >= 0);
	}

	void RegisterElementInstancer(asIScriptEngine *engine)
	{
		// Register the wrapper type for garbage collection
		ElementWrapper<Rocket::Core::Element>::Register(engine);
		// This is the interface that ScriptElement implements
		RegisterElementInterface(engine);
		// The Element type-registration methods
		RegisterBindElementInstancer(engine);
	}

}}
