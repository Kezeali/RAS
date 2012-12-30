template <typename T>
void registerElementMembers(asIScriptEngine *engine, const std::string &name, int excluded_virtual_methods)
{
	// Make sure the given type is derived from Rocket::Core::Element
	static_assert(std::is_base_of<Rocket::Core::Element, T>::value, "This is for registering element types");

	namespace RC = Rocket::Core;

	const char *c_name = name.c_str();
	int r;
	r = engine->RegisterObjectMethod(c_name, "Context& GetContext()", asMETHODPR(RC::Element, GetContext, (), Rocket::Core::Context*), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "void Update()", asMETHOD(RC::Element, Update), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void Render()", asMETHOD(RC::Element, Render), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	// Classes

	// Properties
	r = engine->RegisterObjectMethod(c_name,
		"bool SetProperty(const String &in, const String &in)",
		asMETHODPR(RC::Element, SetProperty, (const Rocket::Core::String &, const Rocket::Core::String &), bool),
		asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name,
		"void RemoveProperty(const String &in)",
		asMETHODPR(RC::Element, RemoveProperty, (const Rocket::Core::String&), void),
		asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name,
		"String GetProperty(const String &in)",
		asMETHODPR(RC::Element, GetProperty<Rocket::Core::String>, (const Rocket::Core::String &), Rocket::Core::String),
		asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name,
		"float ResolveProperty(const String &in, float base_value)",
		asMETHODPR(RC::Element, ResolveProperty, (const Rocket::Core::String&, float), float),
		asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	// Attributes
	r = engine->RegisterObjectMethod(c_name,
		"bool HasAttribute(const String &in)",
		asMETHODPR(RC::Element, HasAttribute, (const Rocket::Core::String &), bool),
		asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name,
		"String GetAttribute(const String &in, const String &in)",
		asMETHODPR(RC::Element, GetAttribute<Rocket::Core::String>, (const Rocket::Core::String &, const Rocket::Core::String &) const, Rocket::Core::String),
		asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name,
		"int GetAttribute(const String &in, const int &in)",
		asMETHODPR(RC::Element, GetAttribute<int>, (const Rocket::Core::String &, const int &) const, int),
		asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name,
		"void RemoveAttribute(const String &in)",
		asMETHODPR(RC::Element, RemoveAttribute, (const Rocket::Core::String&), void),
		asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	// DOM Properties
	r = engine->RegisterObjectMethod(c_name, "const String &GetTagName() const", asMETHOD(RC::Element, GetTagName), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "const String &GetId() const", asMETHOD(RC::Element, GetId), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void SetId(const String &in)", asMETHOD(RC::Element, SetId), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "float GetAbsoluteLeft()", asMETHOD(RC::Element, GetAbsoluteLeft), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetAbsoluteTop()", asMETHOD(RC::Element, GetAbsoluteTop), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "float GetClientLeft()", asMETHOD(RC::Element, GetClientLeft), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetClientTop()", asMETHOD(RC::Element, GetClientTop), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetClientWidth()", asMETHOD(RC::Element, GetClientWidth), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetClientHeight()", asMETHOD(RC::Element, GetClientHeight), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "Element& GetOffsetParent()", asMETHOD(RC::Element, GetOffsetParent), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetOffsetLeft()", asMETHOD(RC::Element, GetOffsetLeft), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetOffsetTop()", asMETHOD(RC::Element, GetOffsetTop), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetOffsetWidth()", asMETHOD(RC::Element, GetOffsetWidth), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetOffsetHeight()", asMETHOD(RC::Element, GetOffsetHeight), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "float GetScrollLeft()", asMETHOD(RC::Element, GetScrollLeft), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void SetScrollLeft(float)", asMETHOD(RC::Element, SetScrollLeft), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetScrollTop()", asMETHOD(RC::Element, GetScrollTop), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void SetScrollTop(float)", asMETHOD(RC::Element, SetScrollTop), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetScrollWidth()", asMETHOD(RC::Element, GetScrollWidth), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetScrollHeight()", asMETHOD(RC::Element, GetScrollHeight), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	if ((excluded_virtual_methods & GetOwnerDocument) != GetOwnerDocument)
	{
		r = engine->RegisterObjectMethod(c_name, "ElementDocument@ GetOwnerDocument()", asFUNCTION(Element_GetOwnerDocument), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register " + name + " class");
	}

	r = engine->RegisterObjectMethod(c_name, "Element& GetParentNode()", asMETHOD(RC::Element, GetParentNode), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "Element& GetNextSibling()", asMETHOD(RC::Element, GetNextSibling), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "Element& GetPreviousSibling()", asMETHOD(RC::Element, GetPreviousSibling), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "Element& GetFirstChild()", asMETHOD(RC::Element, GetFirstChild), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "Element& GetLastChild()", asMETHOD(RC::Element, GetLastChild), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "Element& GetChild(int)", asMETHOD(RC::Element, GetChild), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "int GetNumChildren(bool)", asMETHOD(RC::Element, GetNumChildren), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	if ((excluded_virtual_methods & GetInnerRML) != GetInnerRML)
	{
		r = engine->RegisterObjectMethod(c_name, "void GetInnerRML(String &out) const", asMETHODPR(T, GetInnerRML, (Rocket::Core::String&) const, void), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register " + name + " class");
		r = engine->RegisterObjectMethod(c_name, "String GetInnerRML() const", asMETHODPR(T, GetInnerRML, (void) const, Rocket::Core::String), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register " + name + " class");
	}
	r = engine->RegisterObjectMethod(c_name, "void SetInnerRML(const String &in)", asMETHOD(RC::Element, SetInnerRML), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	// DOM Methods
	r = engine->RegisterObjectMethod(c_name, "bool Focus()", asMETHOD(RC::Element, Focus), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void Blur()", asMETHOD(RC::Element, Blur), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void Click()", asMETHOD(RC::Element, Click), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	// see ras_EventListener.h
	RegisterElementEventListenerMethods(engine, c_name);

	r = engine->RegisterObjectMethod(c_name, "bool DispatchEvent(const String &in, const Dictionary &in, bool)", asMETHOD(RC::Element, DispatchEvent), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "bool DispatchEvent(const String &in, const Dictionary &in)", asFUNCTION(ElemDispatchEvent_default), asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "bool DispatchEvent(const String &in)", asFUNCTION(ElemDispatchEvent_noparams), asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "void ScrollIntoView()", asFUNCTION(ElemScrollIntoView_default), asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void ScrollIntoView(bool)", asMETHOD(RC::Element, ScrollIntoView), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "void AppendChild(Element@, bool)", asFUNCTION(ElemAppendChild), asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void AppendChild(Element@)", asFUNCTION(ElemAppendChild_default), asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void InsertBefore(Element@, Element@)", asMETHOD(RC::Element, InsertBefore), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "bool ReplaceChild(Element@, Element@)", asMETHOD(RC::Element, ReplaceChild), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "bool RemoveChild(Element@)", asFUNCTION(ElemRemoveChild), asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "bool HasChildNodes()", asMETHOD(RC::Element, HasChildNodes), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "Element@ GetElementById(const String &in)", asFUNCTION(Element_GetElementById), asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void  GetElementsByTagName(ElementList &out, const String &in)", asMETHOD(RC::Element, GetElementsByTagName), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
}

template <class T>
void registerDocumentMembers(asIScriptEngine *engine, const std::string &name)
{
	// Make sure the given type is derived from ElementDocument
	static_assert(std::is_base_of<Rocket::Core::ElementDocument, T>::value, "This is for registering ElementDocument derived tyoes");

	const char *c_name = name.c_str();
	int r;
	r = engine->RegisterObjectMethod(c_name, "void SetTitle(const String &in)", asMETHOD(T, SetTitle), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "const String &GetTitle() const", asMETHOD(T, GetTitle), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "void PullToFront()", asMETHOD(T, PullToFront), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void PushToBack()", asMETHOD(T, PushToBack), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "void Show(int)", asMETHOD(T, Show), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void Show()", asFUNCTION(documentShow_Default), asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void Hide()", asMETHOD(T, Hide), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void Close()", asMETHOD(T, Close), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "Element@ CreateElement(const String &in)", asMETHOD(T, CreateElement), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "ElementText@ CreateTextNode(const String &in)", asMETHOD(T, CreateTextNode), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
}
