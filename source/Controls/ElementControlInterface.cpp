/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../../include/Rocket/AngelScript/Controls/ElementControlInterface.h"

#include "../../include/Rocket/AngelScript/Core/registration_utils/RegistrationUtils.h"

#include <ScriptUtils/Inheritance/RegisterConversion.h>

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

		void SetCursorIndex_default(Rocket::Controls::ElementFormControlTextArea* element, int index);
		void ShowCursor_default(Rocket::Controls::ElementFormControlTextArea* element, bool show);

		template <class _ControlType>
		void RegisterFormControlMembers(asIScriptEngine *engine, const char * c_name)
		{
			int r;
			r = engine->RegisterObjectMethod(c_name, "String GetName() const",
				asMETHOD(_ControlType, GetName), asCALL_THISCALL);
			r = engine->RegisterObjectMethod(c_name, "void SetName(const String &in)",
				asMETHOD(_ControlType, SetName), asCALL_THISCALL);

			r = engine->RegisterObjectMethod(c_name, "String GetValue() const",
				asMETHOD(_ControlType, GetValue), asCALL_THISCALL);
			r = engine->RegisterObjectMethod(c_name, "void SetValue(const String &in)",
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
			// The original Add() method
			r = engine->RegisterObjectMethod(c_name, "int Add(const String &in, const String &in, int, bool)",
				asMETHODPR(Rocket::Controls::ElementFormControlSelect, Add, (const Rocket::Core::String&, const Rocket::Core::String&, int, bool), int), asCALL_THISCALL);
			// add with default params. dropped
			r = engine->RegisterObjectMethod(c_name, "int Add(const String &in, const String &in)",
				asFUNCTIONPR(ElementInterface::Add, (Rocket::Controls::ElementFormControlSelect*, const Rocket::Core::String&, const Rocket::Core::String&), int), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod(c_name, "void Remove(int)",
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
			registerType::referenceCountable<Rocket::Controls::ElementDataGrid>(engine, "ElementDataGrid");
			//  DataGrid Row
			registerType::referenceCountable<Rocket::Controls::ElementDataGridRow>(engine, "ElementDataGridRow");
			//  DataGrid Cell
			registerType::referenceCountable<Rocket::Controls::ElementDataGridCell>(engine, "ElementDataGridCell");
			//  DataGrid Expand-Button
			registerType::referenceCountable<Rocket::Controls::ElementDataGridExpandButton>(engine, "ElementDataGridExpandButton");
			//  Form
			registerType::referenceCountable<Rocket::Controls::ElementForm>(engine, "ElementForm");
			//   Form Controls
			registerType::referenceCountable<Rocket::Controls::ElementFormControl>(engine, "ElementFormControl");
			registerType::referenceCountable<Rocket::Controls::ElementFormControlInput>(engine, "ElementFormControlInput");
			registerType::referenceCountable<Rocket::Controls::ElementFormControlTextArea>(engine, "ElementFormControlTextArea");
			registerType::referenceCountable<Rocket::Controls::ElementFormControlSelect>(engine, "ElementFormControlSelect");
			registerType::referenceCountable<Rocket::Controls::ElementFormControlDataSelect>(engine, "ElementFormControlDataSelect");
			//  Tab Set
			registerType::referenceCountable<Rocket::Controls::ElementTabSet>(engine, "ElementTabSet");
			//  SelectOption (value type)
			r = engine->RegisterObjectType("SelectOption", sizeof(Rocket::Controls::SelectOption), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS);

			// Hierarchy (register valid type-casts)
			{
				using namespace ScriptUtils::Inheritance;
				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementDataGrid>(engine, "Element", "ElementDataGrid");

				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementDataGridRow>(engine, "Element", "ElementDataGridRow");

				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementDataGridCell>(engine, "Element", "ElementDataGridCell");

				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementDataGridExpandButton>(engine, "Element", "ElementDataGridExpandButton");

				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementForm>(engine, "Element", "ElementForm");

				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementFormControl>(engine, "Element", "ElementFormControl");

				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementFormControlInput>(engine, "Element", "ElementFormControlInput");
				RegisterBaseOf<Rocket::Controls::ElementFormControl, Rocket::Controls::ElementFormControlInput>(engine, "ElementFormControl", "ElementFormControlInput");

				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementFormControlTextArea>(engine, "Element", "ElementFormControlTextArea");
				RegisterBaseOf<Rocket::Controls::ElementFormControl, Rocket::Controls::ElementFormControlTextArea>(engine, "ElementFormControl", "ElementFormControlTextArea");

				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementFormControlSelect>(engine, "Element", "ElementFormControlSelect");
				RegisterBaseOf<Rocket::Controls::ElementFormControl, Rocket::Controls::ElementFormControlSelect>(engine, "ElementFormControl", "ElementFormControlSelect");

				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementFormControlDataSelect>(engine, "Element", "ElementFormControlDataSelect");
				RegisterBaseOf<Rocket::Controls::ElementFormControl, Rocket::Controls::ElementFormControlDataSelect>(engine, "ElementFormControl", "ElementFormControlDataSelect");

				RegisterBaseOf<Rocket::Core::Element, Rocket::Controls::ElementTabSet>(engine, "Element", "ElementTabSet");
			}


			// ElementDataGrid
			//  Base (Element) members
			registerElementMembers<Rocket::Core::Element>(engine, "ElementDataGrid", _registration_utils::GetInnerRML);
			//  ElementDataGrid methods
			r = engine->RegisterObjectMethod("ElementDataGrid", "bool AddColumn(const String &in, const String &in, float, const String &in)",
				asMETHODPR(Rocket::Controls::ElementDataGrid, AddColumn, (const Rocket::Core::String&, const Rocket::Core::String&, float, const Rocket::Core::String&), bool), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementDataGrid", "void SetDataSource(const String &in)",
				asMETHOD(Rocket::Controls::ElementDataGrid, SetDataSource), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementDataGrid", "int GetNumRows() const",
				asMETHOD(Rocket::Controls::ElementDataGrid, GetRow), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementDataGrid", "ElementDataGridRow& GetRow(int) const",
				asMETHOD(Rocket::Controls::ElementDataGrid, GetRow), asCALL_THISCALL);

			// ElementDataGridRow
			//  Base (Element) members
			registerElementMembers<Rocket::Core::Element>(engine, "ElementDataGridRow");
			//  ElementDataGridRow methods
			r = engine->RegisterObjectMethod("ElementDataGridRow", "void SetRowExpanded(bool)",
				asFUNCTION(ElementInterface::SetRowExpanded), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("ElementDataGridRow", "bool IsRowExpanded()",
				asMETHOD(Rocket::Controls::ElementDataGridRow, IsRowExpanded), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementDataGridRow", "void ExpandRow()",
				asMETHOD(Rocket::Controls::ElementDataGridRow, ExpandRow), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementDataGridRow", "void CollapseRow()",
				asMETHOD(Rocket::Controls::ElementDataGridRow, CollapseRow), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementDataGridRow", "void ToggleRow()",
				asMETHOD(Rocket::Controls::ElementDataGridRow, ToggleRow), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementDataGridRow", "ElementDataGrid& GetParentGrid()",
				asMETHOD(Rocket::Controls::ElementDataGridRow, GetParentGrid), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementDataGridRow", "ElementDataGridRow& GetParentRow()",
				asMETHOD(Rocket::Controls::ElementDataGridRow, GetParentRow), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementDataGridRow", "int GetParentRelativeIndex()",
				asMETHOD(Rocket::Controls::ElementDataGridRow, GetParentRelativeIndex), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementDataGridRow", "int GetTableRelativeIndex()",
				asMETHOD(Rocket::Controls::ElementDataGridRow, GetTableRelativeIndex), asCALL_THISCALL);

			// ElementDataGridCell
			//  Base (Element) members
			registerElementMembers<Rocket::Core::Element>(engine, "ElementDataGridCell");

			// ElementDataGridExpandButton
			//  Base (Element) members
			registerElementMembers<Rocket::Controls::ElementDataGridExpandButton>(engine, "ElementDataGridExpandButton");


			// ElementForm
			//  Base (Element) members
			registerElementMembers<Rocket::Controls::ElementForm>(engine, "ElementForm");
			//  ElementForm methods
			r = engine->RegisterObjectMethod("ElementForm", "void Submit(const String &in, const String &in)",
				asMETHOD(Rocket::Controls::ElementForm, Submit), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementForm", "void Submit()",
				asFUNCTION(ElementInterface::Submit), asCALL_CDECL_OBJFIRST);
			

			// ElementFormControlInput
			//  Base (Element) members
			registerElementMembers<Rocket::Controls::ElementFormControlInput>(engine, "ElementFormControlInput");
			//  Base (ElementFormControl) members
			RegisterFormControlMembers<Rocket::Controls::ElementFormControlInput>(engine, "ElementFormControlInput");
			//  ElementFormControlInput members
			r = engine->RegisterObjectMethod("ElementFormControlInput", "bool GetChecked()",
				asFUNCTION(ElementInterface::GetChecked), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("ElementFormControlInput", "void SetChecked(bool)",
				asFUNCTION(ElementInterface::SetChecked), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("ElementFormControlInput", "int GetMaxLength()",
				asFUNCTION(ElementInterface::GetMaxLength), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("ElementFormControlInput", "void SetMaxLength(int)",
				asFUNCTION(ElementInterface::SetMaxLength), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("ElementFormControlInput", "int GetSize()",
				asFUNCTION(ElementInterface::GetSize), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("ElementFormControlInput", "void SetSize(int)",
				asFUNCTION(ElementInterface::SetSize), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("ElementFormControlInput", "int GetMax()",
				asFUNCTION(ElementInterface::GetMax), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("ElementFormControlInput", "void SetMax(int)",
				asFUNCTION(ElementInterface::SetMax), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("ElementFormControlInput", "int GetMin()",
				asFUNCTION(ElementInterface::GetMin), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("ElementFormControlInput", "void SetMin(int)",
				asFUNCTION(ElementInterface::SetMin), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("ElementFormControlInput", "int GetStep()",
				asFUNCTION(ElementInterface::GetStep), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("ElementFormControlInput", "void SetStep(int)",
				asFUNCTION(ElementInterface::SetStep), asCALL_CDECL_OBJFIRST);

			// ElementFormControlTextArea
			//  Base (Element) members (excluding GetInnerRML, which is defined as private in ElementFormControlTextArea)
			registerElementMembers<Rocket::Core::Element>(engine, "ElementFormControlTextArea", _registration_utils::GetInnerRML);
			//  Base members
			RegisterFormControlMembers<Rocket::Controls::ElementFormControlTextArea>(engine, "ElementFormControlTextArea");
			//  ElementFormControlTextArea members
			r = engine->RegisterObjectMethod("ElementFormControlTextArea", "int GetNumColumns()",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, GetNumColumns), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementFormControlTextArea", "void SetNumColumns(int)",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, SetNumColumns), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementFormControlTextArea", "int GetNumRows()",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, GetNumRows), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementFormControlTextArea", "void SetNumRows(int)",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, SetNumRows), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementFormControlTextArea", "bool GetWordWrap()",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, GetWordWrap), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementFormControlTextArea", "void SetWordWrap(bool)",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, SetWordWrap), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementFormControlTextArea", "int GetMaxLength()",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, GetMaxLength), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementFormControlTextArea", "void SetMaxLength(int)",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, SetMaxLength), asCALL_THISCALL);

			r = engine->RegisterObjectMethod("ElementFormControlTextArea", "int GetCursorIndex() const",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, GetCursorIndex), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementFormControlTextArea", "void SetCursorIndex(int,bool)",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, SetCursorIndex), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementFormControlTextArea", "void SetCursorIndex(int)",
				asFUNCTION(SetCursorIndex_default), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("ElementFormControlTextArea", "void ShowCursor(bool,bool)",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, ShowCursor), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementFormControlTextArea", "void ShowCursor(bool)",
				asFUNCTION(ShowCursor_default), asCALL_CDECL_OBJFIRST);
			r = engine->RegisterObjectMethod("ElementFormControlTextArea", "void ScrollToCursor()",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, ScrollToCursor), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("ElementFormControlTextArea", "const Vector2f &GetCursorPosition() const",
				asMETHOD(Rocket::Controls::ElementFormControlTextArea, GetCursorPosition), asCALL_THISCALL);

			// SelectOption (value type)
			r = engine->RegisterObjectMethod("SelectOption", "Element@ GetElement()",
				asMETHOD(Rocket::Controls::SelectOption, GetElement), asCALL_THISCALL);
			r = engine->RegisterObjectMethod("SelectOption", "const String &GetValue() const",
				asMETHOD(Rocket::Controls::SelectOption, GetValue), asCALL_THISCALL);

			// ElementFormControlSelect
			//  Base (Element) members
			registerElementMembers<Rocket::Controls::ElementFormControl>(engine, "ElementFormControlSelect");
			//  Base members
			RegisterFormControlMembers<Rocket::Controls::ElementFormControlSelect>(engine, "ElementFormControlSelect");
			//  ElementFormControlSelect members
			RegisterFormControlSelectMembers(engine, "ElementFormControlSelect");

			// ElementFormControlDataSelect
			//  Base (Element) members
			registerElementMembers<Rocket::Controls::ElementFormControl>(engine, "ElementFormControlDataSelect");
			//  Base (ElementFormControl) members
			RegisterFormControlMembers<Rocket::Controls::ElementFormControlSelect>(engine, "ElementFormControlDataSelect");
			//  Base (ElementFormControlSelect) members
			RegisterFormControlSelectMembers(engine, "ElementFormControlDataSelect");
			//  ElementFormControlDataSelect members
			engine->RegisterObjectMethod("ElementFormControlDataSelect", "void SetDataSouce(const String &in)",
				asMETHOD(Rocket::Controls::ElementFormControlDataSelect, SetDataSource), asCALL_THISCALL);

			// ElementTabSet
			//  Base (Element) members
			registerElementMembers<Rocket::Core::Element>(engine, "ElementTabSet");
			//  ElementTabSet members
			engine->RegisterObjectMethod("ElementTabSet", "int GetNumTabs()",
				asMETHOD(Rocket::Controls::ElementTabSet, GetNumTabs), asCALL_THISCALL);
			engine->RegisterObjectMethod("ElementTabSet", "void SetTab(int, const String &in)",
				asMETHODPR(Rocket::Controls::ElementTabSet, SetTab, (int, const Rocket::Core::String&), void), asCALL_THISCALL);
			engine->RegisterObjectMethod("ElementTabSet", "void SetPanel(int, const String &in)",
				asMETHODPR(Rocket::Controls::ElementTabSet, SetPanel, (int, const Rocket::Core::String&), void), asCALL_THISCALL);
			engine->RegisterObjectMethod("ElementTabSet", "int GetActiveTab()",
				asMETHOD(Rocket::Controls::ElementTabSet, GetActiveTab), asCALL_THISCALL);
			engine->RegisterObjectMethod("ElementTabSet", "void SetActiveTab(int)",
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

		//int ElementInterface::Add(Rocket::Controls::ElementFormControlSelect* element, const Rocket::Core::String& rml, const Rocket::Core::String& value, asIScriptObject *data, int before, bool selectable)
		//{
		//	data->Release();
		//	return element->Add(rml, value, (void*)data, before, selectable);
		//}

		// Override for ElementFormControlSelect's Add() without the last parameter.
		int ElementInterface::Add(Rocket::Controls::ElementFormControlSelect* element, const Rocket::Core::String& rml, const Rocket::Core::String& value)
		{
			return element->Add(rml, value);
		}

		void SetCursorIndex_default(Rocket::Controls::ElementFormControlTextArea* element, int index)
		{
			element->SetCursorIndex(index);
		}

		void ShowCursor_default(Rocket::Controls::ElementFormControlTextArea* element, bool show)
		{
			element->ShowCursor(show);
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
