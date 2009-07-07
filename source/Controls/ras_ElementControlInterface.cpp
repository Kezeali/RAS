/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../include/Rocket/AngelScript/Controls/ras_ElementControlInterface.h"

#include "../include/Rocket/AngelScript/Core/registration_utils/ras_RegistrationUtils.h"

#include <Inheritance/RegisterConversion.h>

#include <Rocket/Core/Factory.h>
#include <Rocket/Controls/ElementDataGrid.h>
#include <Rocket/Controls/ElementDataGridCell.h>
#include <Rocket/Controls/ElementDataGridRow.h>
#include <Rocket/Controls/ElementDataGridExpandButton.h>
#include <Rocket/Controls/ElementForm.h>
#include <Rocket/Controls/ElementFormControlDataSelect.h>
#include <Rocket/Controls/ElementFormControlInput.h>
#include <Rocket/Controls/ElementFormControlSelect.h>
#include <Rocket/Controls/ElementFormControlTextArea.h>
#include <Rocket/Controls/ElementTabSet.h>

#include <angelscript.h>

namespace Rocket { namespace AngelScript {
	namespace Controls {

		template <class _ControlType>
		void RegisterFormControlMembers(asIScriptEngine *engine, const char * c_name)
		{
			int r;
			r = engine->RegisterObjectMethod(c_name, "e_String GetName() const",
				asMETHOD(_ControlType, GetName), asCALL_THISCALL);
			r = engine->RegisterObjectMethod(c_name, "void SetName(const e_String &in)",
				asMETHOD(_ControlType, SetName), asCALL_THISCALL);

			r = engine->RegisterObjectMethod(c_name, "e_String GetValue() const",
				asMETHOD(_ControlType, GetValue), asCALL_THISCALL);
			r = engine->RegisterObjectMethod(c_name, "void SetValue(const e_String &in)",
				asMETHOD(_ControlType, SetValue), asCALL_THISCALL);

			r = engine->RegisterObjectMethod(c_name, "bool IsDisabled()",
				asMETHOD(_ControlType, IsDisabled), asCALL_THISCALL);
			r = engine->RegisterObjectMethod(c_name, "void SetDisabled(bool)",
				asMETHOD(_ControlType, SetDisabled), asCALL_THISCALL);

			r = engine->RegisterObjectMethod(c_name, "bool IsReadOnly()",
				asMETHOD(_ControlType, IsReadOnly), asCALL_THISCALL);
			r = engine->RegisterObjectMethod(c_name, "void SetReadOnly(bool)",
				asMETHOD(_ControlType, SetReadOnly), asCALL_THISCALL);
		}

		void RegisterFormControlSelectMembers(asIScriptEngine *engine, const char * c_name)
		{
			int r;
			r = engine->RegisterObjectMethod(c_name, "void Add(const e_String &in, const e_String &in, int, bool)",
				asMETHOD(Rocket::Controls::ElementFormControlSelect, Add), asCALL_THISCALL);
			r = engine->RegisterObjectMethod(c_name, "void Add(const e_String &in, const e_String &in)",
				asFUNCTION(ElementInterface::Add), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod(c_name, "void Add(const e_String &in, const e_String &in, int, bool)",
				asMETHOD(Rocket::Controls::ElementFormControlSelect, Remove), asCALL_THISCALL);

			r = engine->RegisterObjectMethod(c_name, "SelectOption& GetOption(int)",
				asMETHOD(Rocket::Controls::ElementFormControlSelect, GetOption), asCALL_THISCALL);
			r = engine->RegisterObjectMethod(c_name, "int GetNumOptions()",
				asMETHOD(Rocket::Controls::ElementFormControlSelect, GetNumOptions), asCALL_THISCALL);
			r = engine->RegisterObjectMethod(c_name, "int GetSelection()",
				asMETHOD(Rocket::Controls::ElementFormControlSelect, GetSelection), asCALL_THISCALL);
			r = engine->RegisterObjectMethod(c_name, "void SetSelection(int)",
				asMETHOD(Rocket::Controls::ElementFormControlSelect, SetSelection), asCALL_THISCALL);
		}

		void ElementInterface::InitialiseAngelScriptInterface(asIScriptEngine *engine)
		{
			using namespace Rocket::AngelScript::_registration_utils;

			int r;
			// Register types

			//  DataGrid
			registerType::referenceCountable<Rocket::Controls::ElementDataGrid>(engine, "DataGrid");
			//  DataGrid Row
			registerType::referenceCountable<Rocket::Controls::ElementDataGridRow>(engine, "DataGridRow");
			//  DataGrid Cell
			registerType::referenceCountable<Rocket::Controls::ElementDataGridCell>(engine, "DataGridCell");
			//  DataGrid Expand-Button
			registerType::referenceCountable<Rocket::Controls::ElementDataGridExpandButton>(engine, "DataGridExpandButton");
			//  Form
			registerType::referenceCountable<Rocket::Controls::ElementForm>(engine, "Form");
			//   Form Controls
			registerType::referenceCountable<Rocket::Controls::ElementFormControl>(engine, "FormControl");
			registerType::referenceCountable<Rocket::Controls::ElementFormControlInput>(engine, "FormControlInput");
			registerType::referenceCountable<Rocket::Controls::ElementFormControlTextArea>(engine, "FormControlTextArea");
			registerType::referenceCountable<Rocket::Controls::ElementFormControlSelect>(engine, "FormControlSelect");
			registerType::referenceCountable<Rocket::Controls::ElementFormControlDataSelect>(engine, "FormControlDataSelect");
			//  Tab Set
			registerType::referenceCountable<Rocket::Controls::ElementTabSet>(engine, "TabSet");
			//  SelectOption (value type)
			r = engine->RegisterObjectType("SelectOption", sizeof(Rocket::Controls::SelectOption), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS);

			// Hierarchy (register valid type-casts)
			{
				using namespace ScriptUtils::Inheritance;
				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementDataGrid>(engine, "Element", "DataGrid");

				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementDataGridRow>(engine, "Element", "DataGridRow");

				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementDataGridCell>(engine, "Element", "DataGridCell");

				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementDataGridExpandButton>(engine, "Element", "DataGridExpandButton");

				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementForm>(engine, "Element", "Form");

				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementFormControl>(engine, "Element", "FormControl");

				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementFormControlInput>(engine, "Element", "FormControlInput");
				RegisterBaseOf<Rocket::Controls::ElementFormControl, Rocket::Controls::ElementFormControlInput>(engine, "FormControl", "FormControlInput");

				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementFormControlTextArea>(engine, "Element", "FormControlTextArea");
				RegisterBaseOf<Rocket::Controls::ElementFormControl, Rocket::Controls::ElementFormControlTextArea>(engine, "FormControl", "FormControlTextArea");

				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementFormControlSelect>(engine, "Element", "FormControlSelect");
				RegisterBaseOf<Rocket::Controls::ElementFormControl, Rocket::Controls::ElementFormControlSelect>(engine, "FormControl", "FormControlSelect");

				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementFormControlDataSelect>(engine, "Element", "FormControlDataSelect");
				RegisterBaseOf<Rocket::Controls::ElementFormControl, Rocket::Controls::ElementFormControlDataSelect>(engine, "FormControl", "FormControlDataSelect");

				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementTabSet>(engine, "Element", "TabSet");
			}


			// ElementDataGrid
			//  Base (Element) members
			registerElementMembers<Rocket::Core::Element>(engine, "DataGrid", _registration_utils::GetInnerRML);
			//  ElementDataGrid methods
			r = engine->RegisterObjectMethod("DataGrid", "bool AddColumn(const e_String &in, const e_String &in, float, const e_String &in)",
				asMETHODPR(Rocket::Controls::ElementDataGrid, AddColumn, (const EMP::Core::String&, const EMP::Core::String&, float, const EMP::Core::String&), bool), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("DataGrid", "void SetDataSource(const e_String &in)",
				asMETHOD(Rocket::Controls::ElementDataGrid, SetDataSource), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("DataGrid", "int GetNumRows() const",
				asMETHOD(Rocket::Controls::ElementDataGrid, GetRow), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("DataGrid", "DataGridRow& GetRow(int) const",
				asMETHOD(Rocket::Controls::ElementDataGrid, GetRow), asCALL_THISCALL);

			// ElementDataGridRow
			//  Base (Element) members
			registerElementMembers<Rocket::Core::Element>(engine, "DataGridRow");
			//  ElementDataGridRow methods
			r = engine->RegisterObjectMethod("DataGridRow", "void SetRowExpanded(bool)",
				asFUNCTION(ElementInterface::SetRowExpanded), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("DataGridRow", "bool IsRowExpanded()",
				asMETHOD(Rocket::Controls::ElementDataGridRow, IsRowExpanded), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("DataGridRow", "void ExpandRow()",
				asMETHOD(Rocket::Controls::ElementDataGridRow, ExpandRow), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("DataGridRow", "void CollapseRow()",
				asMETHOD(Rocket::Controls::ElementDataGridRow, CollapseRow), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("DataGridRow", "void ToggleRow()",
				asMETHOD(Rocket::Controls::ElementDataGridRow, ToggleRow), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("DataGridRow", "DataGrid& GetParentGrid()",
				asMETHOD(Rocket::Controls::ElementDataGridRow, GetParentGrid), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("DataGridRow", "DataGridRow& GetParentRow()",
				asMETHOD(Rocket::Controls::ElementDataGridRow, GetParentRow), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("DataGridRow", "int GetParentRelativeIndex()",
				asMETHOD(Rocket::Controls::ElementDataGridRow, GetParentRelativeIndex), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("DataGridRow", "int GetTableRelativeIndex()",
				asMETHOD(Rocket::Controls::ElementDataGridRow, GetTableRelativeIndex), asCALL_THISCALL);

			// ElementDataGridCell
			//  Base (Element) members
			registerElementMembers<Rocket::Core::Element>(engine, "DataGridCell");

			// ElementDataGridExpandButton
			//  Base (Element) members
			registerElementMembers<Rocket::Controls::ElementDataGridExpandButton>(engine, "DataGridExpandButton");


			// ElementForm
			//  Base (Element) members
			registerElementMembers<Rocket::Controls::ElementForm>(engine, "Form");
			//  ElementForm methods
			r = engine->RegisterObjectMethod("Form", "void Submit(const e_String &in, const e_String &in)",
				asMETHOD(Rocket::Controls::ElementForm, Submit), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("Form", "void Submit()",
				asFUNCTION(ElementInterface::Submit), asCALL_CDECL_OBJFIRST);
			

			// ElementFormControlInput
			//  Base (Element) members
			registerElementMembers<Rocket::Controls::ElementFormControlInput>(engine, "FormControlInput");
			//  Base (ElementFormControl) members
			RegisterFormControlMembers<Rocket::Controls::ElementFormControlInput>(engine, "FormControlInput");
			//  ElementFormControlInput members
			r = engine->RegisterObjectMethod("FormControlInput", "bool GetChecked()",
				asFUNCTION(ElementInterface::GetChecked), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("FormControlInput", "void SetChecked(bool)",
				asFUNCTION(ElementInterface::SetChecked), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("FormControlInput", "int GetMaxLength()",
				asFUNCTION(ElementInterface::GetMaxLength), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("FormControlInput", "void SetMaxLength(int)",
				asFUNCTION(ElementInterface::SetMaxLength), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("FormControlInput", "int GetSize()",
				asFUNCTION(ElementInterface::GetSize), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("FormControlInput", "void SetSize(int)",
				asFUNCTION(ElementInterface::SetSize), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("FormControlInput", "int GetMax()",
				asFUNCTION(ElementInterface::GetMax), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("FormControlInput", "void SetMax(int)",
				asFUNCTION(ElementInterface::SetMax), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("FormControlInput", "int GetMin()",
				asFUNCTION(ElementInterface::GetMin), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("FormControlInput", "void SetMin(int)",
				asFUNCTION(ElementInterface::SetMin), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("FormControlInput", "int GetStep()",
				asFUNCTION(ElementInterface::GetStep), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("FormControlInput", "void SetStep(int)",
				asFUNCTION(ElementInterface::SetStep), asCALL_CDECL_OBJFIRST);

			// ElementFormControlTextArea
			//  Base (Element) members (excluding GetInnerRML, which is defined as private in ElementFormControlTextArea)
			registerElementMembers<Rocket::Core::Element>(engine, "FormControlTextArea", _registration_utils::GetInnerRML);
			//  Base members
			RegisterFormControlMembers<Rocket::Controls::ElementFormControlTextArea>(engine, "FormControlTextArea");
			//  ElementFormControlTextArea members
			r = engine->RegisterObjectMethod("FormControlTextArea", "int GetNumColumns()",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, GetNumColumns), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("FormControlTextArea", "void SetNumColumns(int)",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, SetNumColumns), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("FormControlTextArea", "int GetNumRows()",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, GetNumRows), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("FormControlTextArea", "void SetNumRows(int)",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, SetNumRows), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("FormControlTextArea", "bool GetWordWrap()",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, GetWordWrap), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("FormControlTextArea", "void SetWordWrap(bool)",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, SetWordWrap), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("FormControlTextArea", "int GetMaxLength()",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, GetMaxLength), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("FormControlTextArea", "void SetMaxLength(int)",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, SetMaxLength), asCALL_THISCALL);

			r = engine->RegisterObjectMethod("FormControlTextArea", "int GetCursorIndex() const",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, GetCursorIndex), asCALL_THISCALL);

			// SelectOption (value type)
			r = engine->RegisterObjectMethod("SelectOption", "Element@ GetElement()",
				asMETHOD(Rocket::Controls::SelectOption, GetElement), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("SelectOption", "const e_String &GetValue() const",
				asMETHOD(Rocket::Controls::SelectOption, GetValue), asCALL_THISCALL);

			// ElementFormControlSelect
			//  Base (Element) members
			registerElementMembers<Rocket::Controls::ElementFormControl>(engine, "FormControlSelect");
			//  Base members
			RegisterFormControlMembers<Rocket::Controls::ElementFormControlSelect>(engine, "FormControlSelect");
			//  ElementFormControlSelect members
			RegisterFormControlSelectMembers(engine, "FormControlSelect");

			// ElementFormControlDataSelect
			//  Base (Element) members
			registerElementMembers<Rocket::Controls::ElementFormControl>(engine, "FormControlDataSelect");
			//  Base (ElementFormControl) members
			RegisterFormControlMembers<Rocket::Controls::ElementFormControlSelect>(engine, "FormControlDataSelect");
			//  Base (ElementFormControlSelect) members
			RegisterFormControlSelectMembers(engine, "FormControlDataSelect");
			//  ElementFormControlDataSelect members
			engine->RegisterObjectMethod("FormControlDataSelect", "void SetDataSouce(const e_String &in)",
				asMETHOD(Rocket::Controls::ElementFormControlDataSelect, SetDataSource), asCALL_THISCALL);

			// ElementTabSet
			//  Base (Element) members
			registerElementMembers<Rocket::Core::Element>(engine, "TabSet");
			//  ElementTabSet members
			engine->RegisterObjectMethod("TabSet", "int GetNumTabs()",
				asMETHOD(Rocket::Controls::ElementTabSet, GetNumTabs), asCALL_THISCALL);
			engine->RegisterObjectMethod("TabSet", "void SetTab(int, const e_String &in)",
				asMETHODPR(Rocket::Controls::ElementTabSet, SetTab, (int, const EMP::Core::String&), void), asCALL_THISCALL);
			engine->RegisterObjectMethod("TabSet", "void SetPanel(int, const e_String &in)",
				asMETHODPR(Rocket::Controls::ElementTabSet, SetPanel, (int, const EMP::Core::String&), void), asCALL_THISCALL);
			engine->RegisterObjectMethod("TabSet", "int GetActiveTab()",
				asMETHOD(Rocket::Controls::ElementTabSet, GetActiveTab), asCALL_THISCALL);
			engine->RegisterObjectMethod("TabSet", "void SetActiveTab(int)",
				asMETHOD(Rocket::Controls::ElementTabSet, SetActiveTab), asCALL_THISCALL);
		}

		void ElementInterface::InitialiseRocketInterface()
		{	
		}

		// Sets the expanded state of a data grid row.
		void ElementInterface::SetRowExpanded(Rocket::Controls::ElementDataGridRow* element, bool row_expanded)
		{
			if (row_expanded)
				element->ExpandRow();
			else
				element->CollapseRow();
		}

		// Override for ElementFormControlSelect's Add() without the last parameter.
		int ElementInterface::Add(Rocket::Controls::ElementFormControlSelect* element, const EMP::Core::String& rml, const EMP::Core::String& value)
		{
			return element->Add(rml, value);
		}

		// Default parameter submit for forms
		void ElementInterface::Submit(Rocket::Controls::ElementForm* element)
		{
			element->Submit();
		}

		bool ElementInterface::GetChecked(Rocket::Controls::ElementFormControlInput* element)
		{
			return element->HasAttribute("checked");
		}

		void ElementInterface::SetChecked(Rocket::Controls::ElementFormControlInput* element, bool checked)
		{
			if (checked)
				element->SetAttribute("checked", true);
			else
				element->RemoveAttribute("checked");
		}

		int ElementInterface::GetMaxLength(Rocket::Controls::ElementFormControlInput* element)
		{
			return element->GetAttribute<int>("maxlength", -1);
		}

		void ElementInterface::SetMaxLength(Rocket::Controls::ElementFormControlInput* element, int max_length)
		{
			element->SetAttribute("maxlength", max_length);
		}

		int ElementInterface::GetSize(Rocket::Controls::ElementFormControlInput* element)
		{
			return element->GetAttribute<int>("size", 20);
		}

		void ElementInterface::SetSize(Rocket::Controls::ElementFormControlInput* element, int size)
		{
			element->SetAttribute("size", size);
		}

		int ElementInterface::GetMin(Rocket::Controls::ElementFormControlInput* element)
		{
			return element->GetAttribute<int>("min", 0);
		}

		void ElementInterface::SetMin(Rocket::Controls::ElementFormControlInput* element, int min)
		{
			element->SetAttribute("min", min);
		}

		int ElementInterface::GetMax(Rocket::Controls::ElementFormControlInput* element)
		{
			return element->GetAttribute<int>("max", 100);
		}

		void ElementInterface::SetMax(Rocket::Controls::ElementFormControlInput* element, int max)
		{
			element->SetAttribute("max", max);
		}

		int ElementInterface::GetStep(Rocket::Controls::ElementFormControlInput* element)
		{
			return element->GetAttribute<int>("step", 1);
		}

		void ElementInterface::SetStep(Rocket::Controls::ElementFormControlInput* element, int step)
		{
			element->SetAttribute("step", step);
		}

	}
}}
