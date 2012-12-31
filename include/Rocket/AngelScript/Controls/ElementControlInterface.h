/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_ELEMENTINTERFACE
#define H_ROCKET_AS_ELEMENTINTERFACE

#include <Rocket/Controls/SelectOption.h>

#include <angelscript.h>


namespace Rocket {
	namespace Controls {
		class ElementDataGridRow;
		class ElementForm;
		class ElementFormControlInput;
		class ElementFormControlSelect;
	}

namespace AngelScript { namespace Controls {

	class ElementInterface
	{
	public:
		/// Initialises the python element interface
		static void InitialiseAngelScriptInterface(asIScriptEngine *engine);
		/// Initialise the rocket element interface
		static void InitialiseRocketInterface();

	public:
		// Sets the expanded state of a data grid row.
		static void SetRowExpanded(Rocket::Controls::ElementDataGridRow* element, bool row_expanded);
		//static int Add(Rocket::Controls::ElementFormControlSelect* element, const Rocket::Core::String& rml, const Rocket::Core::String& value, asIScriptObject *data, int before, bool selectable);
		// Override for ElementFormControlSelect's Add() without the last parameter.
		static int Add(Rocket::Controls::ElementFormControlSelect* element, const Rocket::Core::String& rml, const Rocket::Core::String& value);

		// Default parameter submit for forms
		static void Submit(Rocket::Controls::ElementForm* element);

		// Methods for simplyfing access to input element attributes
		static bool GetChecked(Rocket::Controls::ElementFormControlInput* element);
		static void SetChecked(Rocket::Controls::ElementFormControlInput* element, bool checked);

		static int GetMaxLength(Rocket::Controls::ElementFormControlInput* element);
		static void SetMaxLength(Rocket::Controls::ElementFormControlInput* element, int max_length);

		static int GetSize(Rocket::Controls::ElementFormControlInput* element);
		static void SetSize(Rocket::Controls::ElementFormControlInput* element, int size);

		static int GetMax(Rocket::Controls::ElementFormControlInput* element);
		static void SetMax(Rocket::Controls::ElementFormControlInput* element, int max);

		static int GetMin(Rocket::Controls::ElementFormControlInput* element);
		static void SetMin(Rocket::Controls::ElementFormControlInput* element, int min);

		static int GetStep(Rocket::Controls::ElementFormControlInput* element);
		static void SetStep(Rocket::Controls::ElementFormControlInput* element, int step);
	};

}}
}

#endif
