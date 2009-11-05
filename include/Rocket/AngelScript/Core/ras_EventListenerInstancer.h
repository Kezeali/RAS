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
		* Maybe it shouldn't be passed here - maybe in another method (or maybe in another aswell)
		*/
		InlineEventListenerInstancer(asIScriptEngine *engine, const char *module,
			asSFuncPtr line_callback, void *line_callback_obj,
			asSFuncPtr exception_callback, void *exception_callback_obj);

		InlineEventListenerInstancer(asIScriptEngine *engine, const char *module);

		//! IEL
		Core::EventListener* InstanceEventListener(const EMP::Core::String& value);

		//! RLS (ACRONYMS!!)
		virtual void Release();

	protected:
		asIScriptEngine *m_Engine;
		const char *m_DefaultModule;

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