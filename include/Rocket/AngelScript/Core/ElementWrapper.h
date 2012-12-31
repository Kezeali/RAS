/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_ELEMENTWRAPPER
#define H_ROCKET_AS_ELEMENTWRAPPER

#include <Rocket/Core.h>
#include <angelscript.h>

#include <ScriptUtils/Calling/Caller.h>

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
	static_assert(std::is_base_of<Rocket::Core::Element, T>::value, "Element wrapper can only wrap types derived from Rocket::Core::Element.");

	ElementWrapper(const char* tag, asIScriptObject* self)
		: T(tag),
		obj(self),
		gcFlag(false),
		ctx(nullptr),
		released(false)
	{
		obj->AddRef();
	}

	ElementWrapper(const char* tag)
		: T(tag),
		obj(nullptr),
		gcFlag(false),
		ctx(nullptr),
		released(false)
	{
	}

	virtual ~ElementWrapper()
	{
		if (ctx)
			ctx->Release();
	}

	virtual void SetScriptObject(asIScriptObject* self)
	{
		obj = self;
		if (self != nullptr)
			self->AddRef();
	}

	//! Return the AS script-object associated with this element
	virtual void* GetScriptObject() const
	{
		return static_cast<void*>(obj);
	}

	// Add ref to app object (the script object keeps it's own ref count, garbage collection handles the rest)
	virtual void AddReference()
	{
		T::AddReference();
		gcFlag = false;
	}

	// Remove ref from app object
	virtual void RemoveReference()
	{
		ROCKET_ASSERTMSG(!released, "Tried to remove Element ref. after deactivation");
		if (!released)
		{
			gcFlag = false;
			T::RemoveReference();
		}
	}

	virtual void OnReferenceDeactivate()
	{
		released = true;
		//obj->Release(); // Already released by garbage collection at this point
		obj = nullptr;
		delete this;
	}

	// Allows the GC to mark this object
	void SetGCFlag()
	{
		gcFlag = true;
	}

	// Returns true if this object has been marked by the GC
	bool GetGCFlag() const
	{
		return gcFlag;
	}

	void EnumReferences(asIScriptEngine *engine)
	{
		engine->GCEnumCallback((void*)obj);
	}

	void ReleaseAllReferences(asIScriptEngine *engine)
	{
		obj->Release();
	}

	virtual void OnUpdate()
	{
		Core::Element::OnUpdate();

		SC::Caller f = SC::Caller::Create(GetCtx(), obj, "void OnUpdate()");
		if (f)
			f();
		f.set_object(nullptr);
		GetCtx()->Unprepare();
	}

	virtual void OnRender()
	{
		Core::Element::OnRender();

		SC::Caller f = SC::Caller::Create(GetCtx(), obj, "void OnRender()");
		if (f)
			f();
		f.set_object(nullptr);
		GetCtx()->Unprepare();
	}

	virtual void OnLayout()
	{
		Core::Element::OnLayout();

		SC::Caller f = SC::Caller::Create(GetCtx(), obj, "void OnLayout()");
		if (f)
			f();
		f.set_object(nullptr);
		GetCtx()->Unprepare();
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

private:
	// Script representation of this object
	asIScriptObject* obj;
	bool gcFlag;
	asIScriptContext* ctx;

	bool released;

	asIScriptContext* GetCtx()
	{
		if (ctx == nullptr && obj != nullptr)
		{
			ctx = obj->GetEngine()->CreateContext();
		}

		return ctx;
	}
};

template <typename T> int ElementWrapper<T>::TypeId = -1;

void RegisterElementInterface(asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterInterface("IElement");
	ROCKET_ASSERT(r >= 0);
}

}}

#endif
