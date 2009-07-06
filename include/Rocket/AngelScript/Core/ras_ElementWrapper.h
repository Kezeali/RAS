/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_ELEMENTWRAPPER
#define H_ROCKET_AS_ELEMENTWRAPPER

#include <Rocket/Core.h>
#include <angelscript.h>

#include <Inheritance/ScriptObjectWrapper.h>

#include <boost/mpl/assert.hpp>
#include <type_traits>


namespace Rocket { namespace AngelScript {

	namespace SC = ScriptUtils::Calling;
/*!
* AS Wrapper class for Elements 
*/
template <typename T>
class ElementWrapper : public T, public ScriptUtils::Inheritance::ScriptObjectWrapper
{
public:
	BOOST_MPL_ASSERT(( std::tr1::is_base_of<Rocket::Core::Element, T> ));

	ElementWrapper(const char* tag, asIScriptObject* self)
		: T( tag ),
		ScriptUtils::Inheritance::ScriptObjectWrapper( self )
	{
		//T::RemoveReference();
		
		//for (int i = 0; i < this->T::GetReferenceCount(); i++)
		if (T::GetReferenceCount() >= 2)
			_obj->AddRef();
	}

	ElementWrapper(const char* tag)
		: T( tag ),
		ScriptUtils::Inheritance::ScriptObjectWrapper( NULL ),
		locked(false)
	{
	}

	virtual ~ElementWrapper() {}

	virtual void SetScriptObject(asIScriptObject *self)
	{
		//T::RemoveReference();

		set_obj(self);
		//_obj = self;
		
		// i starts at 1 because one reference is already accounted for
		//for (int i = 1; i < this->T::GetReferenceCount(); i++)

		//if (T::GetReferenceCount() >= 2)
		//	_obj->AddRef();
	}

	//! Return the AS script-object associated with this element
	virtual void* GetScriptObject() const
	{
		return static_cast<void*>(_obj);
	}

	// Propogate add ref's into AS mirror obj
	virtual void AddReference()
	{
		T::AddReference();

		//if (_obj != NULL && T::GetReferenceCount() == 2)
		//	_obj->AddRef();

		//if (!locked)
		//{
		//	locked = true;
		//	if (_obj != NULL)
		//		_obj->AddRef();
		//	locked = false;
		//}
	}

	// Propogate remove ref's into AS mirror obj
	virtual void RemoveReference()
	{
		//if (!locked)
		//{
		//	locked = true;
		//	if (_obj != NULL && _obj->Release() == 0)
		//	{
		//		_obj = NULL;
		//		delete this;
		//		return;
		//	}
		//	locked = false;
		//}

		if (_obj != NULL && T::GetReferenceCount() == 2)
		{
			if (_obj->Release() == 1)
			{
				// Pre-empt garbage collection
				asIScriptObject *temp = _obj;
				_obj = NULL;
				temp->Release();
			}
		}

		if (!locked)
			T::RemoveReference();
		else
			EMP_ASSERTMSG(!locked, "Tried to remove Element ref. after deactivation");
	}

	virtual void OnReferenceDeactivate()
	{
		locked = true;
		//_obj->GetEngine()->GarbageCollect();
		_obj = NULL;
		delete this;
	}

	virtual void OnUpdate()
	{
		Core::Element::OnUpdate();

		SC::Caller f = this->get_caller("void OnUpdate()");
		if ( f.ok() )
			f();
	}

	virtual void OnRender()
	{
		Core::Element::OnRender();

		SC::Caller f = this->get_caller("void OnRender()");
		if ( f.ok() )
			f();
	}

	virtual void OnLayout()
	{
		Core::Element::OnLayout();

		SC::Caller f = this->get_caller("void OnLayout()");
		if ( f.ok() )
			f();
	}

	bool locked;

//private:
	// AS representation (mirror) of this object
	//asIScriptObject* m_ScrObj;
};

void RegisterElementInterface(asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterInterface("IElement");
	EMP_ASSERT(r >= 0);

	//r = engine->RegisterInterfaceMethod("IElement", "void OnUpdate()");
	//EMP_ASSERT(r >= 0);
	//r = engine->RegisterInterfaceMethod("IElement", "void OnRender()");
	//EMP_ASSERT(r >= 0);
}

}}

#endif
