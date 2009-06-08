/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../include/registration_utils/ras_RegistrationUtils.h"

//#include "ras_RefCountedWrapper.h"


namespace Rocket { namespace AngelScript { namespace _registration_utils {

	//class RefCounted_RString : public Rocket::Core::String
	//{
	//	int m_RefCount;

	//public:
	//	RefCounted_RString()
	//		: Rocket::Core::String()
	//	{
	//	}

	//	RefCounted_RString(const char *utf8_string)
	//		: Rocket::Core::String(utf8_string)
	//	{
	//	}

	//	void AddRef()
	//	{
	//		++m_RefCount;
	//	}

	//	void Release()
	//	{
	//		if (--m_RefCount)
	//			delete this;
	//	}
	//};

	//RefCounted_RString *stringToRStringRef(CScriptString *script_string)
	//{
	//	RefCounted_RString *rString = new RefCounted_RString(script_string->buffer.c_str());
	//	script_string->Release();
	//	return rString;
	//}


	bool rocketStringsEqual(const Rocket::Core::String& l, const Rocket::Core::String& r)
	{
		return l == r;
	}

	bool rocketStringsNotEqual(const Rocket::Core::String& l, const Rocket::Core::String& r)
	{
		return !(l == r);
	}

	Rocket::Core::StringBase::size_type rocketStringFindNpos(Rocket::Core::String *object, const Rocket::Core::String& s)
	{
		return object->Find(s, Rocket::Core::StringBase::npos);
	}

	Rocket::Core::StringBase::size_type rocketStringFind(Rocket::Core::String *object, const Rocket::Core::String& s, Rocket::Core::StringBase::size_type pos)
	{
		return object->Find(s, pos);
	}

	static const Rocket::Core::StringBase::size_type rocketStringNpos()
	{
		return Rocket::Core::StringBase::npos;
	}

	static void constructRString(Rocket::Core::String *ptr)
	{
		new(ptr) Rocket::Core::String();
	}

	static void destructRString(Rocket::Core::String *ptr)
	{
		ptr->~String();
	}

	void registerRString(asIScriptEngine *engine)
	{
		int r;
		r = engine->RegisterObjectType("r_String", sizeof(Rocket::Core::String), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
		if (r < 0)
			throw Exception("Couldn't register Rocket String type");

		r = engine->RegisterObjectBehaviour("r_String",
			asBEHAVE_CONSTRUCT,
			"void f()",
			asFUNCTION(constructRString),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Rocket String type");

		r = engine->RegisterObjectBehaviour("r_String",
			asBEHAVE_DESTRUCT,
			"void f()",
			asFUNCTION(destructRString),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Rocket String type");

		r = engine->RegisterObjectBehaviour("r_String",
			asBEHAVE_ASSIGNMENT,
			"r_String &f(r_String &in)",
			asMETHODPR(Rocket::Core::String, operator=, (const Rocket::Core::String&), Rocket::Core::String&),
			asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Rocket String type");

		r = engine->RegisterGlobalBehaviour(asBEHAVE_EQUAL,
			"bool f(const r_String &in, const r_String &in)",
			asFUNCTION(rocketStringsEqual),
			asCALL_CDECL);
		if (r < 0)
			throw Exception("Couldn't register Rocket String type");

		r = engine->RegisterGlobalBehaviour(asBEHAVE_NOTEQUAL,
			"bool f(const r_String &in, const r_String &in)",
			asFUNCTION(rocketStringsNotEqual),
			asCALL_CDECL);
		if (r < 0)
			throw Exception("Couldn't register Rocket String type");

		r = engine->RegisterObjectMethod("r_String",
			"uint Find(const r_String &in)",
			asFUNCTION(rocketStringFindNpos),
			asCALL_CDECL_OBJFIRST);
		if (r < 0)
			throw Exception("Couldn't register Rocket String type");

		r = engine->RegisterObjectMethod("r_String",
			"uint Find(const r_String &in, uint)",
			asFUNCTION(rocketStringFind),
			asCALL_CDECL_OBJFIRST);
		if (r < 0)
			throw Exception("Couldn't register Rocket String type");

		//engine->RegisterObjectBehaviour("r_String", asBEHAVE_ADDREF, "void f()", asMETHOD(RefCountedString, AddRef), asCALL_THISCALL);
		//engine->RegisterObjectBehaviour("r_String", asBEHAVE_RELEASE, "void f()", asMETHOD(RefCountedString, Release), asCALL_THISCALL);

		// String behaviour
		//engine->RegisterObjectBehaviour("string", asBEHAVE_IMPLICIT_VALUE_CAST, "r_String f()", asFUNCTION(stringToRString), asCALL_CDECL_OBJFIRST);
	}

	bool eStringsEqual(const Rocket::Core::String& l, const Rocket::Core::String& r)
	{
		return l == r;
	}

	bool eStringsNotEqual(const Rocket::Core::String& l, const Rocket::Core::String& r)
	{
		return !(l == r);
	}

	Rocket::Core::StringBase::size_type eStringFindNpos(const Rocket::Core::String& s, Rocket::Core::String *object)
	{
		return object->Find(s, Rocket::Core::StringBase::npos);
	}

	Rocket::Core::StringBase::size_type eStringFind(const Rocket::Core::String& s, Rocket::Core::StringBase::size_type pos, Rocket::Core::String *object)
	{
		return object->Find(s, pos);
	}

	static const Rocket::Core::StringBase::size_type eStringNpos()
	{
		return Rocket::Core::StringBase::npos;
	}

	static void constructEString(Rocket::Core::String *ptr)
	{
		new(ptr) Rocket::Core::String();
	}

	static void destructEString(Rocket::Core::String *ptr)
	{
		ptr->~String();
	}

	void registerEString(asIScriptEngine *engine)
	{
		int r;
		r = engine->RegisterObjectType("e_String", sizeof(EMP::Core::String), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
		if (r < 0)
			throw Exception("Couldn't register EMP String type");

		// String behaviours
		r = engine->RegisterObjectBehaviour("e_String",
			asBEHAVE_CONSTRUCT,
			"void f()",
			asFUNCTION(constructEString),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register EMP String type");

		r = engine->RegisterObjectBehaviour("e_String",
			asBEHAVE_DESTRUCT,
			"void f()",
			asFUNCTION(destructEString),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register EMP String type");

		r = engine->RegisterObjectBehaviour("e_String",
			asBEHAVE_ASSIGNMENT,
			"e_String &f(e_String &in)",
			asMETHODPR(EMP::Core::String, operator=, (const EMP::Core::String&), EMP::Core::String&),
			asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register EMP String type");

		r = engine->RegisterGlobalBehaviour(asBEHAVE_EQUAL,
			"bool f(const e_String &in, const e_String &in)",
			asFUNCTION(eStringsEqual),
			asCALL_CDECL);
		if (r < 0)
			throw Exception("Couldn't register EMP String type");

		r = engine->RegisterGlobalBehaviour(asBEHAVE_NOTEQUAL,
			"bool f(const e_String &in, const e_String &in)",
			asFUNCTION(eStringsNotEqual),
			asCALL_CDECL);
		if (r < 0)
			throw Exception("Couldn't register EMP String type");

		// Methods
		r = engine->RegisterObjectMethod("e_String",
			"uint Find(const e_String &in)",
			asFUNCTION(eStringFindNpos),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register EMP String type");

		r = engine->RegisterObjectMethod("e_String",
			"uint Find(const e_String &in, uint)",
			asFUNCTION(eStringFind),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register EMP String type");
	}

	void ContextUnloadDocument(const EMP::Core::String &name, Core::Context *obj)
	{
		obj->UnloadDocument( obj->GetDocument(name) );
	}

	void registerContextMembers(asIScriptEngine *engine)
	{
		int r;
		// Context Behaviours

		// Context Methods
		r = engine->RegisterObjectMethod("Context", "e_String GetName()", asMETHOD(Rocket::Core::Context, GetName), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");

		r = engine->RegisterObjectMethod("Context", "e_Vector2i GetDimensions()", asMETHOD(Rocket::Core::Context, GetDimensions), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");
		r = engine->RegisterObjectMethod("Context", "void SetDimensions(const e_Vector2i &in)", asMETHOD(Rocket::Core::Context, SetDimensions), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");

		r = engine->RegisterObjectMethod("Context", "bool Update()", asMETHOD(Rocket::Core::Context, Update), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");
		r = engine->RegisterObjectMethod("Context", "bool Render()", asMETHOD(Rocket::Core::Context, Render), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");

		r = engine->RegisterObjectMethod("Context", "Document& GetDocument(const e_String &in)", asMETHODPR(Rocket::Core::Context, GetDocument, (const EMP::Core::String &), Rocket::Core::ElementDocument*), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");
		r = engine->RegisterObjectMethod("Context", "Document& GetDocument(int)", asMETHODPR(Rocket::Core::Context, GetDocument, (int), Rocket::Core::ElementDocument*), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");
		r = engine->RegisterObjectMethod("Context", "int GetNumDocuments()", asMETHOD(Rocket::Core::Context, GetNumDocuments), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");

		r = engine->RegisterObjectMethod("Context", "Element& GetFocusElement()", asMETHOD(Rocket::Core::Context, GetFocusElement), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");
		r = engine->RegisterObjectMethod("Context", "Element& GetHoverElement()", asMETHOD(Rocket::Core::Context, GetFocusElement), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");
		r = engine->RegisterObjectMethod("Context", "Element& GetRootElement()", asMETHOD(Rocket::Core::Context, GetRootElement), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");


		r = engine->RegisterObjectMethod("Context", "void AddEventListener(const e_String &in, EventListener@, bool)", asMETHOD(Rocket::Core::Context, AddEventListener), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");
		r = engine->RegisterObjectMethod("Context", "void RemoveEventListener(const e_String &in, EventListener@, bool)", asMETHOD(Rocket::Core::Context, AddEventListener), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");

		r = engine->RegisterObjectMethod("Context", "Document@ CreateDocument(const e_String &in)", asMETHOD(Rocket::Core::Context, CreateDocument), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");
		r = engine->RegisterObjectMethod("Context", "Document@ LoadDocument(const e_String &in)", asMETHODPR(Rocket::Core::Context, LoadDocument, (const EMP::Core::String&), Rocket::Core::ElementDocument*), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");
		r = engine->RegisterObjectMethod("Context", "Document@ LoadDocumentFromString(const e_String &in)", asMETHOD(Rocket::Core::Context, LoadDocumentFromMemory), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");
		r = engine->RegisterObjectMethod("Context", "void UnloadDocument(Document@)", asMETHOD(Rocket::Core::Context, UnloadDocument), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");
		r = engine->RegisterObjectMethod("Context", "void UnloadDocument(const e_String &in)", asFUNCTION(ContextUnloadDocument), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Context type");
		r = engine->RegisterObjectMethod("Context", "void UnloadAllDocuments()", asMETHOD(Rocket::Core::Context, UnloadAllDocuments), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");

		r = engine->RegisterObjectMethod("Context", "void AddMouseCursor(Document@)", asMETHOD(Rocket::Core::Context, AddMouseCursor), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");
		r = engine->RegisterObjectMethod("Context", "Document@ LoadMouseCursor(const e_String &in)", asMETHOD(Rocket::Core::Context, LoadMouseCursor), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");
		r = engine->RegisterObjectMethod("Context", "void UnloadMouseCursor(const e_String &in)", asMETHOD(Rocket::Core::Context, UnloadMouseCursor), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");
		r = engine->RegisterObjectMethod("Context", "void UnloadAllMouseCursors()", asMETHOD(Rocket::Core::Context, UnloadAllMouseCursors), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");
		r = engine->RegisterObjectMethod("Context", "bool SetMouseCursor(const e_String &in)", asMETHOD(Rocket::Core::Context, SetMouseCursor), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");
		r = engine->RegisterObjectMethod("Context", "bool ShowMouseCursor(bool)", asMETHOD(Rocket::Core::Context, ShowMouseCursor), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Context type");
	}

	void registerFocusFlagsEnum(asIScriptEngine *engine)
	{
		int r;
		r = engine->RegisterEnum("DocumentFocusFlags");
		if (r < 0)
			throw Exception("Couldn't register FocusFlags enum");
		r = engine->RegisterEnumValue("DocumentFocusFlags", "NONE", Rocket::Core::ElementDocument::NONE);
		if (r < 0)
			throw Exception("Couldn't register FocusFlags enum");
		r = engine->RegisterEnumValue("DocumentFocusFlags", "FOCUS", Rocket::Core::ElementDocument::FOCUS);
		if (r < 0)
			throw Exception("Couldn't register FocusFlags enum");
		r = engine->RegisterEnumValue("DocumentFocusFlags", "MODAL", Rocket::Core::ElementDocument::MODAL);
		if (r < 0)
			throw Exception("Couldn't register FocusFlags enum");
	}

	bool eventIsOfType(const EMP::Core::String &type, Rocket::Core::Event *obj)
	{
		return *obj == type;
	}

	//! Registers Event#GetParameter<R>()
	template <typename R>
	void registerEventGetParameter(asIScriptEngine *engine, const std::string &R_typename)
	{
		int r;
		r = engine->RegisterObjectMethod("Event",
			C_STR(R_typename + " GetParameter(const e_String &in, const " + R_typename + " &in)"),
			asMETHODPR(Rocket::Core::Event, GetParameter<R>, (const EMP::Core::String &, const R &), R),
			asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Event::GetParameter<" + R_typename + ">");
	}

	EMP::Core::String EventGetType(Rocket::Core::Event *obj)
	{
		return obj->GetType();
	}

	void registerEventMembers(asIScriptEngine *engine)
	{
		int r;
		// Behaviours
		//  event == string (type)
		// removed because typeA == typeB operator is not defined in AS
		/*r = engine->RegisterObjectBehaviour("Event", asBEHAVE_EQUAL, "bool f(const e_String &in)", asFUNCTION(eventIsOfType), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Event type");*/

		// Methods
		r = engine->RegisterObjectMethod("Event", "Element& GetCurrentElement()", asMETHOD(Rocket::Core::Event, GetCurrentElement), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Event type");

		r = engine->RegisterObjectMethod("Event", "Element& GetTargetElement()", asMETHOD(Rocket::Core::Event, GetTargetElement), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Event type");

		/*r = engine->RegisterObjectMethod("Event", "e_String GetType()", asMETHOD(Rocket::Core::Event, GetType), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Event type");*/
		r = engine->RegisterObjectMethod("Event", "e_String GetType()", asFUNCTION(EventGetType), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Event type");

		registerEventGetParameter<int>(engine, as_primative_name<int>());
		registerEventGetParameter<float>(engine, as_primative_name<float>());
		//! \todo TODO: Perhaps these shouldn't be registered here - they rely on types that may not be registered
		//  perhaps: GetParameter<EMP::Core::Vector2i> could be registered in registerType::vector2<int>
		registerEventGetParameter<EMP::Core::Vector2i>(engine, "e_Vector2i");
		registerEventGetParameter<EMP::Core::Vector2f>(engine, "e_Vector2f");
		registerEventGetParameter<EMP::Core::String>(engine, "e_String");

		r = engine->RegisterObjectMethod("Event", "e_Dictionary &GetParameters()", asMETHOD(Rocket::Core::Event, GetParameters), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Event type");
	}

	void registerEventListenerMembers(asIScriptEngine *engine)
	{
		int r;
		r = engine->RegisterInterfaceMethod("EventListener", "void ProcessEvent(Event &inout)");
		if (r < 0)
			throw Exception("Couldn't register EventListener type");
		r = engine->RegisterInterfaceMethod("EventListener", "void OnAttach(Element&)");
		if (r < 0)
			throw Exception("Couldn't register EventListener type");
		r = engine->RegisterInterfaceMethod("EventListener", "void OnDetach(Element&)");
		if (r < 0)
			throw Exception("Couldn't register EventListener type");
	}

	void documentShow_Default(Rocket::Core::ElementDocument *obj)
	{
		obj->Show();
	}

	void ElemAppendChild_default(Rocket::Core::Element *element, Rocket::Core::Element *obj)
	{
		obj->AppendChild(element, true);
	}

}}}
