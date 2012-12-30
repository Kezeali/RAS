#ifndef H_SCRIPT_ELEMENTS
#define H_SCRIPT_ELEMENTS

#include <angelscript.h>

namespace Rocket { namespace AngelScript { 
	int AddElementsScriptSection(asIScriptEngine *engine, const char *module_name)
	{
		const char* script =
			"\n"
			"class ScriptElement : Rocket::IElement\n"
			"{\n"
			"Rocket::Element@ __inner;\n"
			"ScriptElement(Rocket::Element@ appObj) { @__inner = @appObj; }\n"
			"void _SetAppObject(Rocket::Element@ newInner) { @__inner = @newInner; }\n"
			"Rocket::Element@ _GetAppObject() { return __inner; }\n"
			"Context@ GetContext() { return __inner.GetContext(); }\n"
			"void Update() { __inner.Update(); }\n"
			"void Render() { __inner.Render(); }\n"
			"bool SetProperty(const Rocket::String&in p1, const Rocket::String&in p2) { return __inner.SetProperty(p1, p2); }\n"
			"void RemoveProperty(const Rocket::String&in p1) { __inner.RemoveProperty(p1); }\n"
			"Rocket::String GetProperty(const Rocket::String&in p1) { return __inner.GetProperty(p1); }\n"
			"float ResolveProperty(const Rocket::String&in p1, float p2) { return __inner.ResolveProperty(p1, p2); }\n"
			"Rocket::String GetTagName() const { return __inner.GetTagName(); }\n"
			"Rocket::String GetId() const { return __inner.GetId(); }\n"
			"void SetId(const Rocket::String&in p1) { __inner.SetId(p1); }\n"
			"float GetAbsoluteLeft() { return __inner.GetAbsoluteLeft(); }\n"
			"float GetAbsoluteTop() { return __inner.GetAbsoluteTop(); }\n"
			"float GetClientLeft() { return __inner.GetClientLeft(); }\n"
			"float GetClientTop() { return __inner.GetClientTop(); }\n"
			"float GetClientWidth() { return __inner.GetClientWidth(); }\n"
			"float GetClientHeight() { return __inner.GetClientHeight(); }\n"
			"Rocket::Element@ GetOffsetParent() { return __inner.GetOffsetParent(); }\n"
			"float GetOffsetLeft() { return __inner.GetOffsetLeft(); }\n"
			"float GetOffsetTop() { return __inner.GetOffsetTop(); }\n"
			"float GetOffsetWidth() { return __inner.GetOffsetWidth(); }\n"
			"float GetOffsetHeight() { return __inner.GetOffsetHeight(); }\n"
			"float GetScrollLeft() { return __inner.GetScrollLeft(); }\n"
			"void SetScrollLeft(float p1) { __inner.SetScrollLeft(p1); }\n"
			"float GetScrollTop() { return __inner.GetScrollTop(); }\n"
			"void SetScrollTop(float p1) { __inner.SetScrollTop(p1); }\n"
			"float GetScrollWidth() { return __inner.GetScrollWidth(); }\n"
			"float GetScrollHeight() { return __inner.GetScrollHeight(); }\n"
			"Rocket::ElementDocument@ GetOwnerDocument() { return __inner.GetOwnerDocument(); }\n"
			"Rocket::Element@ GetParentNode() { return __inner.GetParentNode(); }\n"
			"Rocket::Element@ GetNextSibling() { return __inner.GetNextSibling(); }\n"
			"Rocket::Element@ GetPreviousSibling() { return __inner.GetPreviousSibling(); }\n"
			"Rocket::Element@ GetFirstChild() { return __inner.GetFirstChild(); }\n"
			"Rocket::Element@ GetLastChild() { return __inner.GetLastChild(); }\n"
			"Rocket::Element@ GetChild(int p1) { return __inner.GetChild(p1); }\n"
			"int GetNumChildren(bool p1) { return __inner.GetNumChildren(p1); }\n"
			"void GetInnerRML(Rocket::String&out p1) { __inner.GetInnerRML(p1); }\n"
			"void SetInnerRML(const Rocket::String&in p1) { __inner.SetInnerRML(p1); }\n"
			"bool Focus() { return __inner.Focus(); }\n"
			"void Blur() { __inner.Blur(); }\n"
			"void Click() { __inner.Click(); }\n"
			"void AddEventListener(const Rocket::String&in p1, Rocket::IEventListener@ p2, bool p3) { __inner.AddEventListener(p1, p2, p3); }\n"
			"void AddEventListener(const Rocket::String&in p1, Rocket::IEventListener@ p2) { __inner.AddEventListener(p1, p2); }\n"
			"void AddEventListener(const Rocket::String&in p1, const Rocket::String&in p2, bool p3) { __inner.AddEventListener(p1, p2, p3); }\n"
			"void AddEventListener(const Rocket::String&in p1, const Rocket::String&in p2) { __inner.AddEventListener(p1, p2); }\n"
			"bool DispatchEvent(const Rocket::String&in p1, const Rocket::Dictionary&in p2, bool p3) { return __inner.DispatchEvent(p1, p2, p3); }\n"
			"bool DispatchEvent(const Rocket::String&in p1, const Rocket::Dictionary&in p2) { return __inner.DispatchEvent(p1, p2); }\n"
			"bool DispatchEvent(const Rocket::String&in p1) { return __inner.DispatchEvent(p1); }\n"
			"void ScrollIntoView(bool p1) { __inner.ScrollIntoView(p1); }\n"
			"void AppendChild(Rocket::Element@ p1, bool p2) { __inner.AppendChild(p1, p2); }\n"
			"void AppendChild(Rocket::Element@ p1) { __inner.AppendChild(p1); }\n"
			"void InsertBefore(Rocket::Element@ p1, Rocket::Element@ p2) { __inner.InsertBefore(p1, p2); }\n"
			"bool ReplaceChild(Rocket::Element@ p1, Rocket::Element@ p2) { return __inner.ReplaceChild(p1, p2); }\n"
			"bool RemoveChild(Rocket::Element@ p1) { return __inner.RemoveChild(p1); }\n"
			"bool HasChildNodes() { return __inner.HasChildNodes(); }\n"
			"Rocket::Element@ GetElementById(const Rocket::String&in p1) { return __inner.GetElementById(p1); }\n"
			"void GetElementsByTagName(Rocket::ElementList&out p1, const Rocket::String&in p2) { __inner.GetElementsByTagName(p1, p2); }\n"
			"}\n"
			"\n";

		asPWORD copy = engine->GetEngineProperty(asEP_COPY_SCRIPT_SECTIONS);
		engine->SetEngineProperty(asEP_COPY_SCRIPT_SECTIONS, 0);

		asIScriptModule* module = engine->GetModule(module_name, asGM_CREATE_IF_NOT_EXISTS);
		int r = module->AddScriptSection("Elements", script);

		engine->SetEngineProperty(asEP_COPY_SCRIPT_SECTIONS, copy);
		return r;
	}
}}

#endif
