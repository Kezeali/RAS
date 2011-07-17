/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_ELEMENTWRAPPER
#define H_ROCKET_AS_ELEMENTWRAPPER

#include <Rocket/Core.h>
#include <angelscript.h>

#include <ScriptUtils/Calling/Caller.h>

#include <boost/mpl/assert.hpp>
#include <type_traits>


namespace Rocket { namespace AngelScript {

	namespace SC = ScriptUtils::Calling;
/*!
* AS Wrapper class for Elements 
*/
template <typename T>
class ElementWrapper : public T
{
public:
	static_assert( std::is_base_of<Rocket::Core::Element, T>::value, "Element wrapper can only wrap types derrived from Rocket::Core::Element." );

	ElementWrapper(const char* tag, asIScriptObject* self)
		: T( tag ),
		_obj( self ),
		m_GCFlag( false ),
		locked( false )
	{
		_obj->AddRef();
	}

	ElementWrapper(const char* tag)
		: T( tag ),
		_obj( nullptr ),
		m_GCFlag( false ),
		locked( false )
	{
	}

	virtual ~ElementWrapper() {}

	virtual void SetScriptObject(asIScriptObject* self)
	{
		_obj = self;
		if (self != nullptr)
			self->AddRef();
	}

	//! Return the AS script-object associated with this element
	virtual void* GetScriptObject() const
	{
		return static_cast<void*>(_obj);
	}

	// Add ref to app object (the script object keeps it's own ref count, garbage collection handles the rest)
	virtual void AddReference()
	{
		T::AddReference();
		m_GCFlag = false;
	}

	// Remove ref from app object
	virtual void RemoveReference()
	{
		if (!locked)
		{
			m_GCFlag = false;
			T::RemoveReference();
		}
		else
			ROCKET_ASSERTMSG(!locked, "Tried to remove Element ref. after deactivation");
	}

	virtual void OnReferenceDeactivate()
	{
		locked = true;
		//_obj->Release(); // Already released by garbage collection at this point
		_obj = nullptr;
		delete this;
	}

	// Allows the GC to mark this object
	void SetGCFlag()
	{
		m_GCFlag = true;
	}

	// Returns true if this object has been marked by the GC
	bool GetGCFlag() const
	{
		return m_GCFlag;
	}

	void EnumReferences(asIScriptEngine *engine)
	{
		engine->GCEnumCallback((void*)_obj);
	}

	void ReleaseAllReferences(asIScriptEngine *engine)
	{
		_obj->Release();
	}

	virtual void OnUpdate()
	{
		Core::Element::OnUpdate();

		SC::Caller f = ScriptUtils::Calling::Caller(_obj, "void OnUpdate()");
		if ( f )
			f();
	}

	virtual void OnRender()
	{
		Core::Element::OnRender();

		SC::Caller f = ScriptUtils::Calling::Caller(_obj, "void OnRender()");
		if ( f )
			f();
	}

	virtual void OnLayout()
	{
		Core::Element::OnLayout();

		SC::Caller f = ScriptUtils::Calling::Caller(_obj, "void OnLayout()");
		if ( f )
			f();
	}

	static int TypeId;

	static void Register(asIScriptEngine* engine)
	{
		const char* name = "RASElementWrapper";
		engine->RegisterObjectType(name, 0, asOBJ_REF | asOBJ_GC);

		// --- Note that the TypeId is recorded here ---
		TypeId = engine->GetTypeIdByDecl(name);

		engine->RegisterObjectBehaviour(name, asBEHAVE_ADDREF, "void f()", asMETHOD(ElementWrapper, AddReference), asCALL_THISCALL);
		engine->RegisterObjectBehaviour(name, asBEHAVE_RELEASE, "void f()", asMETHOD(ElementWrapper, RemoveReference), asCALL_THISCALL);

		// GC behaviours
		engine->RegisterObjectBehaviour(name, asBEHAVE_SETGCFLAG,
			"void f()", asMETHOD(ElementWrapper, SetGCFlag), asCALL_THISCALL);
		engine->RegisterObjectBehaviour(name, asBEHAVE_GETGCFLAG,
			"bool f()", asMETHOD(ElementWrapper, GetGCFlag), asCALL_THISCALL);
		engine->RegisterObjectBehaviour(name, asBEHAVE_GETREFCOUNT,
			"int f()", asMETHOD(ElementWrapper, GetReferenceCount), asCALL_THISCALL);
		engine->RegisterObjectBehaviour(name, asBEHAVE_ENUMREFS,
			"void f(int&in)", asMETHOD(ElementWrapper, EnumReferences), asCALL_THISCALL);
		engine->RegisterObjectBehaviour(name, asBEHAVE_RELEASEREFS,
			"void f(int&in)", asMETHOD(ElementWrapper, ReleaseAllReferences), asCALL_THISCALL);
	}

	bool locked;

private:
	// Script representation of this object
	asIScriptObject* _obj;
	bool m_GCFlag;
};

template <typename T> int ElementWrapper<T>::TypeId = -1;

void RegisterElementInterface(asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterInterface("IElement");
	ROCKET_ASSERT(r >= 0);

	//r = engine->RegisterInterfaceMethod("IElement", "void OnUpdate()");
	//ROCKET_ASSERT(r >= 0);
	//r = engine->RegisterInterfaceMethod("IElement", "void OnRender()");
	//ROCKET_ASSERT(r >= 0);
}

}}

#endif
