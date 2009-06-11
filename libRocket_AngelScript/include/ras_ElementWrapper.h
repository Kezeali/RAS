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
		T::RemoveReference();
		
		for (int i = 0; i < this->T::GetReferenceCount(); i++)
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

		//set_obj(self);
		_obj = self;
		
		// i starts at 1 because one reference is already accounted for
		for (int i = 1; i < this->T::GetReferenceCount(); i++)
			_obj->AddRef();
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

		if (!locked)
		{
			locked = true;
			if (_obj != NULL)
				_obj->AddRef();
			locked = false;
		}
	}

	// Propogate remove ref's into AS mirror obj
	virtual void RemoveReference()
	{
		if (!locked)
		{
			locked = true;
			if (_obj != NULL && _obj->Release() == 0)
			{
				_obj = NULL;
				delete this;
				return;
			}
			locked = false;
		}

		T::RemoveReference();
	}

	virtual void OnUpdate()
	{
		SC::Caller f = this->get_caller("void OnUpdate()");
		if ( f.ok() )
			f();
	}

	virtual void OnRender()
	{
		SC::Caller f = this->get_caller("void OnRender()");
		if ( f.ok() )
			f();
	}

	virtual void OnReferenceDeactivate()
	{
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

	r = engine->RegisterInterfaceMethod("IElement", "void OnUpdate()");
	EMP_ASSERT(r >= 0);
	r = engine->RegisterInterfaceMethod("IElement", "void OnRender()");
	EMP_ASSERT(r >= 0);
}

}}

#endif
