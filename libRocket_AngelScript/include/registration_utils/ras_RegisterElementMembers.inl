template <typename T>
void registerElementMembers<T>(asIScriptEngine *engine, const std::string &name)
{
	// Make sure the given type is derrived from Rocket::Core::Element
	BOOST_MPL_ASSERT(( std::tr1::is_base_of<Rocket::Core::Element, T> ));

	const char *c_name = name.c_str();
	int r;
	r = engine->RegisterObjectMethod(c_name, "Context& GetContext()", asMETHOD(T, GetContext), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "void Update()", asMETHOD(T, Update), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void Render()", asMETHOD(T, Render), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	// Classes

	// Properties
	r = engine->RegisterObjectMethod(c_name,
		"bool SetProperty(const e_String &in, const e_String &in)",
		asMETHODPR(T, SetProperty, (const EMP::Core::String &, const EMP::Core::String &), bool),
		asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void RemoveProperty(const e_String &in)", asMETHOD(T, RemoveProperty), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name,
		"e_String GetProperty(const e_String &in)",
		asMETHODPR(T, GetProperty<EMP::Core::String>, (const EMP::Core::String &), EMP::Core::String),
		asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float ResolveProperty(const e_String &in, float base_value)", asMETHOD(T, ResolveProperty), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	// Attributes

	// DOM Properties
	r = engine->RegisterObjectMethod(c_name, "e_String GetTagName()", asMETHOD(T, GetTagName), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "e_String GetId()", asMETHOD(T, GetId), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void SetId(const e_String &in)", asMETHOD(T, SetId), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "float GetAbsoluteLeft()", asMETHOD(T, GetAbsoluteLeft), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetAbsoluteTop()", asMETHOD(T, GetAbsoluteTop), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "float GetClientLeft()", asMETHOD(T, GetClientLeft), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetClientTop()", asMETHOD(T, GetClientTop), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetClientWidth()", asMETHOD(T, GetClientWidth), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetClientHeight()", asMETHOD(T, GetClientHeight), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "Element& GetOffsetParent()", asMETHOD(T, GetOffsetParent), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetOffsetLeft()", asMETHOD(T, GetOffsetLeft), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetOffsetTop()", asMETHOD(T, GetOffsetTop), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetOffsetWidth()", asMETHOD(T, GetOffsetWidth), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetOffsetHeight()", asMETHOD(T, GetOffsetHeight), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "float GetScrollLeft()", asMETHOD(T, GetScrollLeft), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void SetScrollLeft(float)", asMETHOD(T, SetScrollLeft), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetScrollTop()", asMETHOD(T, GetScrollTop), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void SetScrollTop(float)", asMETHOD(T, SetScrollTop), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetScrollWidth()", asMETHOD(T, GetScrollWidth), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "float GetScrollHeight()", asMETHOD(T, GetScrollHeight), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "Document& GetOwnerDocument()", asMETHOD(T, GetOwnerDocument), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "Element& GetParentNode()", asMETHOD(T, GetParentNode), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "Element& GetNextSibling()", asMETHOD(T, GetNextSibling), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "Element& GetPreviousSibling()", asMETHOD(T, GetPreviousSibling), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "Element& GetFirstChild()", asMETHOD(T, GetFirstChild), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "Element& GetLastChild()", asMETHOD(T, GetLastChild), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "Element& GetChild(int)", asMETHOD(T, GetChild), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "int GetNumChildren(bool)", asMETHOD(T, GetNumChildren), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "void GetInnerRML(e_String &out)", asMETHOD(T, GetInnerRML), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void SetInnerRML(const e_String &in)", asMETHOD(T, SetInnerRML), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	// DOM Methods
	r = engine->RegisterObjectMethod(c_name, "bool Focus()", asMETHOD(T, Focus), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void Blur()", asMETHOD(T, Blur), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void Click()", asMETHOD(T, Click), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "void AddEventListener(const e_String &in, EventListener@, bool)", asMETHOD(T, AddEventListener), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void RemoveEventListener(const e_String &in, EventListener@, bool)", asMETHOD(T, RemoveEventListener), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void DispatchEvent(const e_String &in, const e_Dictionary &in, bool)", asMETHOD(T, DispatchEvent), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "void ScrollIntoView(bool)", asMETHOD(T, ScrollIntoView), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "void AppendChild(Element@, bool)", asMETHOD(T, AppendChild), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void AppendChild(Element@)", asFUNCTION(ElemAppendChild_default), asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void InsertBefore(Element@, Element@)", asMETHOD(T, InsertBefore), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "bool ReplaceChild(Element@, Element@)", asMETHOD(T, ReplaceChild), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "bool RemoveChild(Element@)", asMETHOD(T, RemoveChild), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "bool HasChildNodes()", asMETHOD(T, HasChildNodes), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");

	r = engine->RegisterObjectMethod(c_name, "Element& GetElementById(const e_String &in)", asMETHOD(T, GetElementById), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "void  GetElementsByTag(ElementList &out, const e_String &in)", asMETHOD(T, GetElementsByTag), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
}

template <class T>
void registerDocumentMembers<T>(asIScriptEngine *engine, const std::string &name)
{
	// Make sure the given type is derrived from ElementDocument
	BOOST_MPL_ASSERT(( std::tr1::is_base_of<Rocket::Core::ElementDocument, T> ));

	const char *c_name = name.c_str();
	int r;
	r = engine->RegisterObjectMethod(c_name, "void SetTitle(e_String &in)", asMETHOD(T, SetTitle), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "e_String GetTitle()", asMETHOD(T, GetTitle), asCALL_THISCALL);
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

	r = engine->RegisterObjectMethod(c_name, "Element@ CreateElement(const e_String &in)", asMETHOD(T, CreateElement), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
	r = engine->RegisterObjectMethod(c_name, "ElementText@ CreateTextNode(const e_String &in)", asMETHOD(T, CreateTextNode), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + name + " class");
}
