/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_EVENTLISTENERINSTANCER
#define H_ROCKET_AS_EVENTLISTENERINSTANCER

#include <Rocket/Core/EventListener.h>
#include <Rocket/Core/EventListenerInstancer.h>
#include <angelscript.h>


namespace Rocket { namespace AngelScript {

	//! Creates a script code executor for an inline (RML) defined event
	class InlineEventListenerInstancer : public Rocket::Core::EventListenerInstancer
	{
	public:
		//! CTOR
		/*!
		* \todo Pass a exception callback (which can then be passed to InlineEventListener instances)
		* so exceptions can be logged / displayed by the app. A line callback might be nice too.
		* Maybe it shouldn't be passed here - maybe in another method (or maybe in another as well)
		*/
		InlineEventListenerInstancer(asIScriptEngine *engine,
			asSFuncPtr line_callback, void *line_callback_obj,
			asSFuncPtr exception_callback, void *exception_callback_obj);

		//! CTOR
		InlineEventListenerInstancer(asIScriptEngine *engine);

		//! IEL
		Core::EventListener* InstanceEventListener(const Rocket::Core::String& value, Rocket::Core::Element* element);

		//! RLS (ACRONYMS!!)
		virtual void Release();

	protected:
		asIScriptEngine *m_Engine;

		int m_NextId;


		struct CallbackObj
		{
			CallbackObj() {}
			CallbackObj(asSFuncPtr fn, void *obj) : callback_fn(fn), callback_obj(obj) {}

			asSFuncPtr callback_fn;
			void *callback_obj;
		};

		CallbackObj m_LineCallback;
		CallbackObj m_ExceptionCallback;
	};

}}

#endif