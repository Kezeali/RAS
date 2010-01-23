/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../include/Rocket/AngelScript/Core/registration_utils/ras_RegistrationUtils.h"

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


	bool rocketStringEqual(const Rocket::Core::String& other, Rocket::Core::String *obj)
	{
		return *obj == other;
	}

	Rocket::Core::StringBase::size_type rocketStringFind_fromStart(Rocket::Core::String *object, const Rocket::Core::String& s)
	{
		return object->Find(s);
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

		r = engine->RegisterObjectMethod("r_String",
			"r_String &opAssign(r_String &in)",
			asMETHODPR(Rocket::Core::String, operator=, (const Rocket::Core::String&), Rocket::Core::String&),
			asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Rocket String type");

		r = engine->RegisterObjectMethod("r_String",
			"bool opEquals(const r_String &in)",
			asFUNCTION(rocketStringEqual),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Rocket String type");

		r = engine->RegisterObjectMethod("r_String",
			"uint Find(const r_String &in)",
			asFUNCTION(rocketStringFind_fromStart),
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

	bool eStringEqual(const EMP::Core::String& other, EMP::Core::String* obj)
	{
		return *obj == other;
	}

	EMP::Core::String eStringAdd(const EMP::Core::String& other, EMP::Core::String* obj)
	{
		return *obj + other;
	}

	EMP::Core::String eStringIndex(EMP::Core::String::size_type index, EMP::Core::String *object)
	{
		return object->Substring(index, 1);
	}

	EMP::Core::String::size_type eStringFind_fromStart(const EMP::Core::String& s, EMP::Core::String *object)
	{
		return object->Find(s);
	}

	EMP::Core::String::size_type eStringFind(const EMP::Core::String& s, EMP::Core::String::size_type pos, EMP::Core::String *object)
	{
		return object->Find(s, pos);
	}

	static const EMP::Core::String::size_type eStringNpos()
	{
		return EMP::Core::String::npos;
	}

	EMP::Core::String eStringSubstring_toEnd(EMP::Core::String::size_type start, EMP::Core::String *object)
	{
		return object->Substring(start);
	}

	EMP::Core::String eStringSubstring(EMP::Core::String::size_type start, EMP::Core::String::size_type length, EMP::Core::String *object)
	{
		return object->Substring(start, length);
	}

	static void eStringConstruct(EMP::Core::String *ptr)
	{
		new(ptr) EMP::Core::String();
	}

	static void eStringDestruct(EMP::Core::String *ptr)
	{
		ptr->~StringBase();
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
			asFUNCTION(eStringConstruct),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register EMP String type");

		r = engine->RegisterObjectBehaviour("e_String",
			asBEHAVE_DESTRUCT,
			"void f()",
			asFUNCTION(eStringDestruct),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register EMP String type");

		r = engine->RegisterObjectMethod("e_String",
			"e_String &opAssign(e_String &in)",
			asMETHODPR(EMP::Core::String, operator=, (const EMP::Core::String&), EMP::Core::String&),
			asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register EMP String type");

		r = engine->RegisterObjectMethod("e_String",
			"e_String &opAddAssign(e_String &in)",
			asMETHODPR(EMP::Core::String, operator+=, (const EMP::Core::String&), EMP::Core::String&),
			asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register EMP String type");

		r = engine->RegisterObjectMethod("e_String",
			"bool opEquals(const e_String &in)",
			asFUNCTION(eStringEqual),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register EMP String type");

		r = engine->RegisterObjectMethod("e_String",
			"e_String opAdd(const e_String &in)",
			asFUNCTION(eStringAdd),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register EMP String type");

		r = engine->RegisterObjectBehaviour("e_String",
			asBEHAVE_INDEX,
			"e_String opIndex(uint)",
			asFUNCTION(eStringIndex),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register EMP String index");

		// Methods
		r = engine->RegisterObjectMethod("e_String",
			"bool Empty() const",
			asMETHOD(EMP::Core::String, Empty),
			asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register EMP::Core::String::Empty");

		r = engine->RegisterObjectMethod("e_String",
			"void Clear()",
			asMETHOD(EMP::Core::String, Clear),
			asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register EMP::Core::String::Clear");

		r = engine->RegisterObjectMethod("e_String",
			"uint Length() const",
			asMETHOD(EMP::Core::String, Length),
			asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register EMP::Core::String::Length");

		r = engine->RegisterObjectMethod("e_String",
			"uint Find(const e_String &in)",
			asFUNCTION(eStringFind_fromStart),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register EMP String Find (default)");

		r = engine->RegisterObjectMethod("e_String",
			"uint Find(const e_String &in, uint)",
			asFUNCTION(eStringFind),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register EMP String Find");

		r = engine->RegisterObjectMethod("e_String",
			"uint npos()",
			asFUNCTION(eStringNpos),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register EMP String type");

		r = engine->RegisterObjectMethod("e_String",
			"e_String Substring(uint)",
			asFUNCTION(eStringSubstring_toEnd),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register EMP String Substring (default)");

		r = engine->RegisterObjectMethod("e_String",
			"e_String Substring(uint, uint)",
			asFUNCTION(eStringSubstring),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register EMP String Substring");

		r = engine->RegisterObjectMethod("e_String",
			"e_String ToUpper()",
			asMETHOD(EMP::Core::String, ToUpper),
			asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register EMP::Core::String::ToUpper");
		r = engine->RegisterObjectMethod("e_String",
			"e_String ToLower()",
			asMETHOD(EMP::Core::String, ToLower),
			asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register EMP::Core::String::ToLower");

		r = engine->RegisterObjectMethod("e_String",
			"void Resize(uint)",
			asMETHOD(EMP::Core::String, Resize),
			asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register EMP::Core::String::Resize");
	}

	Rocket::Core::ElementDocument *ContextCreateDocument_default(Core::Context &obj)
	{
		return obj.CreateDocument();
	}

	void ContextUnloadDocument(const EMP::Core::String &name, Core::Context &obj)
	{
		obj.UnloadDocument( obj.GetDocument(name) );
	}

	void registerContextMembers(asIScriptEngine *engine)
	{
		int r;
		// Context Behaviours

		// Context Methods
		r = engine->RegisterObjectMethod("Context", "const e_String &GetName() const", asMETHOD(Rocket::Core::Context, GetName), asCALL_THISCALL);
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

		// See ras_EventListener.h
		RegisterContextEventListenerMethods(engine);

		r = engine->RegisterObjectMethod("Context", "Document@ CreateDocument()", asFUNCTION(ContextCreateDocument_default), asCALL_CDECL_OBJLAST);
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

	void registerKeyIdentifierEnum(asIScriptEngine *engine)
	{
		int r;
		r = engine->RegisterEnum("GUIKey");
		if (r < 0)
			throw Exception("Couldn't register GUIKey enum");

		engine->RegisterEnumValue("GUIKey", "KI_UNKNOWN", Rocket::Core::Input::KI_UNKNOWN);
		engine->RegisterEnumValue("GUIKey", "KI_SPACE", Rocket::Core::Input::KI_SPACE);

		engine->RegisterEnumValue("GUIKey", "KI_0", Rocket::Core::Input::KI_0);
		engine->RegisterEnumValue("GUIKey", "KI_1", Rocket::Core::Input::KI_1);
		engine->RegisterEnumValue("GUIKey", "KI_2", Rocket::Core::Input::KI_2);
		engine->RegisterEnumValue("GUIKey", "KI_3", Rocket::Core::Input::KI_3);
		engine->RegisterEnumValue("GUIKey", "KI_4", Rocket::Core::Input::KI_4);
		engine->RegisterEnumValue("GUIKey", "KI_5", Rocket::Core::Input::KI_5);
		engine->RegisterEnumValue("GUIKey", "KI_6", Rocket::Core::Input::KI_6);
		engine->RegisterEnumValue("GUIKey", "KI_7", Rocket::Core::Input::KI_7);
		engine->RegisterEnumValue("GUIKey", "KI_8", Rocket::Core::Input::KI_8);
		engine->RegisterEnumValue("GUIKey", "KI_9", Rocket::Core::Input::KI_9);

		engine->RegisterEnumValue("GUIKey", "KI_A", Rocket::Core::Input::KI_A);
		engine->RegisterEnumValue("GUIKey", "KI_B", Rocket::Core::Input::KI_B);
		engine->RegisterEnumValue("GUIKey", "KI_C", Rocket::Core::Input::KI_C);
		engine->RegisterEnumValue("GUIKey", "KI_D", Rocket::Core::Input::KI_D);
		engine->RegisterEnumValue("GUIKey", "KI_E", Rocket::Core::Input::KI_E);
		engine->RegisterEnumValue("GUIKey", "KI_F", Rocket::Core::Input::KI_F);
		engine->RegisterEnumValue("GUIKey", "KI_G", Rocket::Core::Input::KI_G);
		engine->RegisterEnumValue("GUIKey", "KI_H", Rocket::Core::Input::KI_H);
		engine->RegisterEnumValue("GUIKey", "KI_I", Rocket::Core::Input::KI_I);
		engine->RegisterEnumValue("GUIKey", "KI_J", Rocket::Core::Input::KI_J);
		engine->RegisterEnumValue("GUIKey", "KI_K", Rocket::Core::Input::KI_K);
		engine->RegisterEnumValue("GUIKey", "KI_L", Rocket::Core::Input::KI_L);
		engine->RegisterEnumValue("GUIKey", "KI_M", Rocket::Core::Input::KI_M);
		engine->RegisterEnumValue("GUIKey", "KI_N", Rocket::Core::Input::KI_N);
		engine->RegisterEnumValue("GUIKey", "KI_O", Rocket::Core::Input::KI_O);
		engine->RegisterEnumValue("GUIKey", "KI_P", Rocket::Core::Input::KI_P);
		engine->RegisterEnumValue("GUIKey", "KI_Q", Rocket::Core::Input::KI_Q);
		engine->RegisterEnumValue("GUIKey", "KI_R", Rocket::Core::Input::KI_R);
		engine->RegisterEnumValue("GUIKey", "KI_S", Rocket::Core::Input::KI_S);
		engine->RegisterEnumValue("GUIKey", "KI_T", Rocket::Core::Input::KI_T);
		engine->RegisterEnumValue("GUIKey", "KI_U", Rocket::Core::Input::KI_U);
		engine->RegisterEnumValue("GUIKey", "KI_V", Rocket::Core::Input::KI_V);
		engine->RegisterEnumValue("GUIKey", "KI_W", Rocket::Core::Input::KI_W);
		engine->RegisterEnumValue("GUIKey", "KI_X", Rocket::Core::Input::KI_X);
		engine->RegisterEnumValue("GUIKey", "KI_Y", Rocket::Core::Input::KI_Y);
		engine->RegisterEnumValue("GUIKey", "KI_Z", Rocket::Core::Input::KI_Z);

		engine->RegisterEnumValue("GUIKey", "KI_OEM_1", Rocket::Core::Input::KI_OEM_1);
		engine->RegisterEnumValue("GUIKey", "KI_OEM_PLUS", Rocket::Core::Input::KI_OEM_PLUS);
		engine->RegisterEnumValue("GUIKey", "KI_OEM_COMMA", Rocket::Core::Input::KI_OEM_COMMA);
		engine->RegisterEnumValue("GUIKey", "KI_OEM_MINUS", Rocket::Core::Input::KI_OEM_MINUS);
		engine->RegisterEnumValue("GUIKey", "KI_OEM_PERIOD", Rocket::Core::Input::KI_OEM_PERIOD);
		engine->RegisterEnumValue("GUIKey", "KI_OEM_2", Rocket::Core::Input::KI_OEM_2);
		engine->RegisterEnumValue("GUIKey", "KI_OEM_3", Rocket::Core::Input::KI_OEM_3);

		engine->RegisterEnumValue("GUIKey", "KI_OEM_4", Rocket::Core::Input::KI_OEM_4);
		engine->RegisterEnumValue("GUIKey", "KI_OEM_5", Rocket::Core::Input::KI_OEM_5);
		engine->RegisterEnumValue("GUIKey", "KI_OEM_6", Rocket::Core::Input::KI_OEM_6);
		engine->RegisterEnumValue("GUIKey", "KI_OEM_7", Rocket::Core::Input::KI_OEM_7);
		engine->RegisterEnumValue("GUIKey", "KI_OEM_8", Rocket::Core::Input::KI_OEM_8);

		engine->RegisterEnumValue("GUIKey", "KI_OEM_102", Rocket::Core::Input::KI_OEM_102);

		engine->RegisterEnumValue("GUIKey", "KI_NUMPAD0", Rocket::Core::Input::KI_NUMPAD0);
		engine->RegisterEnumValue("GUIKey", "KI_NUMPAD1", Rocket::Core::Input::KI_NUMPAD1);
		engine->RegisterEnumValue("GUIKey", "KI_NUMPAD2", Rocket::Core::Input::KI_NUMPAD2);
		engine->RegisterEnumValue("GUIKey", "KI_NUMPAD3", Rocket::Core::Input::KI_NUMPAD3);
		engine->RegisterEnumValue("GUIKey", "KI_NUMPAD4", Rocket::Core::Input::KI_NUMPAD4);
		engine->RegisterEnumValue("GUIKey", "KI_NUMPAD5", Rocket::Core::Input::KI_NUMPAD5);
		engine->RegisterEnumValue("GUIKey", "KI_NUMPAD6", Rocket::Core::Input::KI_NUMPAD6);
		engine->RegisterEnumValue("GUIKey", "KI_NUMPAD7", Rocket::Core::Input::KI_NUMPAD7);
		engine->RegisterEnumValue("GUIKey", "KI_NUMPAD8", Rocket::Core::Input::KI_NUMPAD8);
		engine->RegisterEnumValue("GUIKey", "KI_NUMPAD9", Rocket::Core::Input::KI_NUMPAD9);
		engine->RegisterEnumValue("GUIKey", "KI_NUMPADENTER", Rocket::Core::Input::KI_NUMPADENTER);
		engine->RegisterEnumValue("GUIKey", "KI_MULTIPLY", Rocket::Core::Input::KI_MULTIPLY);
		engine->RegisterEnumValue("GUIKey", "KI_ADD", Rocket::Core::Input::KI_ADD);
		engine->RegisterEnumValue("GUIKey", "KI_SEPARATOR", Rocket::Core::Input::KI_SEPARATOR);
		engine->RegisterEnumValue("GUIKey", "KI_SUBTRACT", Rocket::Core::Input::KI_SUBTRACT);
		engine->RegisterEnumValue("GUIKey", "KI_DECIMAL", Rocket::Core::Input::KI_DECIMAL);
		engine->RegisterEnumValue("GUIKey", "KI_DIVIDE", Rocket::Core::Input::KI_DIVIDE);

		engine->RegisterEnumValue("GUIKey", "KI_BACK", Rocket::Core::Input::KI_BACK);
		engine->RegisterEnumValue("GUIKey", "KI_TAB", Rocket::Core::Input::KI_TAB);

		engine->RegisterEnumValue("GUIKey", "KI_CLEAR", Rocket::Core::Input::KI_CLEAR);
		engine->RegisterEnumValue("GUIKey", "KI_RETURN", Rocket::Core::Input::KI_RETURN);

		engine->RegisterEnumValue("GUIKey", "KI_PAUSE", Rocket::Core::Input::KI_PAUSE);
		engine->RegisterEnumValue("GUIKey", "KI_CAPITAL", Rocket::Core::Input::KI_CAPITAL);

		engine->RegisterEnumValue("GUIKey", "KI_ESCAPE", Rocket::Core::Input::KI_ESCAPE);

		engine->RegisterEnumValue("GUIKey", "KI_PRIOR", Rocket::Core::Input::KI_PRIOR);
		engine->RegisterEnumValue("GUIKey", "KI_NEXT", Rocket::Core::Input::KI_NEXT);
		engine->RegisterEnumValue("GUIKey", "KI_END", Rocket::Core::Input::KI_END);
		engine->RegisterEnumValue("GUIKey", "KI_HOME", Rocket::Core::Input::KI_HOME);
		engine->RegisterEnumValue("GUIKey", "KI_LEFT", Rocket::Core::Input::KI_LEFT);
		engine->RegisterEnumValue("GUIKey", "KI_UP", Rocket::Core::Input::KI_UP);
		engine->RegisterEnumValue("GUIKey", "KI_RIGHT", Rocket::Core::Input::KI_RIGHT);
		engine->RegisterEnumValue("GUIKey", "KI_DOWN", Rocket::Core::Input::KI_DOWN);
		engine->RegisterEnumValue("GUIKey", "KI_SELECT", Rocket::Core::Input::KI_SELECT);
		engine->RegisterEnumValue("GUIKey", "KI_PRINT", Rocket::Core::Input::KI_PRINT);
		engine->RegisterEnumValue("GUIKey", "KI_EXECUTE", Rocket::Core::Input::KI_EXECUTE);
		engine->RegisterEnumValue("GUIKey", "KI_SNAPSHOT", Rocket::Core::Input::KI_SNAPSHOT);
		engine->RegisterEnumValue("GUIKey", "KI_INSERT", Rocket::Core::Input::KI_INSERT);
		engine->RegisterEnumValue("GUIKey", "KI_DELETE", Rocket::Core::Input::KI_DELETE);
		engine->RegisterEnumValue("GUIKey", "KI_HELP", Rocket::Core::Input::KI_HELP);

		engine->RegisterEnumValue("GUIKey", "KI_LWIN", Rocket::Core::Input::KI_LWIN);
		engine->RegisterEnumValue("GUIKey", "KI_RWIN", Rocket::Core::Input::KI_RWIN);
		engine->RegisterEnumValue("GUIKey", "KI_APPS", Rocket::Core::Input::KI_APPS);

		engine->RegisterEnumValue("GUIKey", "KI_F1", Rocket::Core::Input::KI_F1);
		engine->RegisterEnumValue("GUIKey", "KI_F2", Rocket::Core::Input::KI_F2);
		engine->RegisterEnumValue("GUIKey", "KI_F3", Rocket::Core::Input::KI_F3);
		engine->RegisterEnumValue("GUIKey", "KI_F4", Rocket::Core::Input::KI_F4);
		engine->RegisterEnumValue("GUIKey", "KI_F5", Rocket::Core::Input::KI_F5);
		engine->RegisterEnumValue("GUIKey", "KI_F6", Rocket::Core::Input::KI_F6);
		engine->RegisterEnumValue("GUIKey", "KI_F7", Rocket::Core::Input::KI_F7);
		engine->RegisterEnumValue("GUIKey", "KI_F8", Rocket::Core::Input::KI_F8);
		engine->RegisterEnumValue("GUIKey", "KI_F9", Rocket::Core::Input::KI_F9);
		engine->RegisterEnumValue("GUIKey", "KI_F10", Rocket::Core::Input::KI_F10);
		engine->RegisterEnumValue("GUIKey", "KI_F11", Rocket::Core::Input::KI_F11);
		engine->RegisterEnumValue("GUIKey", "KI_F12", Rocket::Core::Input::KI_F12);

		engine->RegisterEnumValue("GUIKey", "KI_NUMLOCK", Rocket::Core::Input::KI_NUMLOCK);
		engine->RegisterEnumValue("GUIKey", "KI_SCROLL", Rocket::Core::Input::KI_SCROLL);

		engine->RegisterEnumValue("GUIKey", "KI_LSHIFT", Rocket::Core::Input::KI_LSHIFT);
		engine->RegisterEnumValue("GUIKey", "KI_RSHIFT", Rocket::Core::Input::KI_RSHIFT);
		engine->RegisterEnumValue("GUIKey", "KI_LCONTROL", Rocket::Core::Input::KI_LCONTROL);
		engine->RegisterEnumValue("GUIKey", "KI_RCONTROL", Rocket::Core::Input::KI_RCONTROL);
		engine->RegisterEnumValue("GUIKey", "KI_LMENU", Rocket::Core::Input::KI_LMENU);
		engine->RegisterEnumValue("GUIKey", "KI_RMENU", Rocket::Core::Input::KI_RMENU);

		engine->RegisterEnumValue("GUIKey", "KI_LMETA", Rocket::Core::Input::KI_LMETA);
		engine->RegisterEnumValue("GUIKey", "KI_RMETA", Rocket::Core::Input::KI_RMETA);
	}

	void registerKeyModifierEnum(asIScriptEngine *engine)
	{
		int r;
		r = engine->RegisterEnum("GUIKeyModifier");
		if (r < 0)
			throw Exception("Couldn't register GUIKeyModifier enum");
		r = engine->RegisterEnumValue("GUIKeyModifier", "KM_CTRL", Rocket::Core::Input::KM_CTRL);
		if (r < 0)
			throw Exception("Couldn't register GUIKeyModifier::KM_CTRL");
		r = engine->RegisterEnumValue("GUIKeyModifier", "KM_SHIFT", Rocket::Core::Input::KM_SHIFT);
		if (r < 0)
			throw Exception("Couldn't register GUIKeyModifier::KM_SHIFT");
		r = engine->RegisterEnumValue("GUIKeyModifier", "KM_ALT", Rocket::Core::Input::KM_ALT);
		if (r < 0)
			throw Exception("Couldn't register GUIKeyModifier::KM_ALT");
		r = engine->RegisterEnumValue("GUIKeyModifier", "KM_META", Rocket::Core::Input::KM_META);
		if (r < 0)
			throw Exception("Couldn't register GUIKeyModifier::KM_META");
		r = engine->RegisterEnumValue("GUIKeyModifier", "KM_CAPSLOCK", Rocket::Core::Input::KM_CAPSLOCK);
		if (r < 0)
			throw Exception("Couldn't register GUIKeyModifier::KM_CAPSLOCK");
		r = engine->RegisterEnumValue("GUIKeyModifier", "KM_NUMLOCK", Rocket::Core::Input::KM_NUMLOCK);
		if (r < 0)
			throw Exception("Couldn't register GUIKeyModifier::KM_NUMLOCK");
		r = engine->RegisterEnumValue("GUIKeyModifier", "KM_SCROLLLOCK", Rocket::Core::Input::KM_SCROLLLOCK);
		if (r < 0)
			throw Exception("Couldn't register GUIKeyModifier::KM_SCROLLLOCK");
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

	Rocket::Core::Element *EventGetCurrentElement(Rocket::Core::Event *obj)
	{
		Rocket::Core::Element *current = obj->GetCurrentElement();
		if (current != NULL)
			current->AddReference();
		return current;
	}

	Rocket::Core::Element *EventGetTargetElement(Rocket::Core::Event *obj)
	{
		Rocket::Core::Element *target = obj->GetTargetElement();
		if (target != NULL)
			target->AddReference();
		return target;
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
			throw Exception("Couldn't register Event::GetCurrentElement");

		r = engine->RegisterObjectMethod("Event", "Element& GetTargetElement()", asMETHOD(Rocket::Core::Event, GetTargetElement), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Event::GetTargetElement");
		//r = engine->RegisterObjectMethod("Event", "Element@ GetCurrentElement() const", asFUNCTION(EventGetCurrentElement), asCALL_CDECL_OBJLAST);
		//if (r < 0)
		//	throw Exception("Couldn't register Event type");

		//r = engine->RegisterObjectMethod("Event", "Element@ GetTargetElement() const", asFUNCTION(EventGetTargetElement), asCALL_CDECL_OBJLAST);
		//if (r < 0)
		//	throw Exception("Couldn't register Event type");

		//r = engine->RegisterObjectMethod("Event", "const e_String &GetType() const", asMETHOD(Rocket::Core::Event, GetType), asCALL_THISCALL);
		//if (r < 0)
		//	throw Exception("Couldn't register Event type");
		r = engine->RegisterObjectMethod("Event", "e_String GetType()", asFUNCTION(EventGetType), asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register Event::GetType");

		registerEventGetParameter<bool>(engine, as_primative_name<bool>());
		registerEventGetParameter<int>(engine, as_primative_name<int>());
		registerEventGetParameter<float>(engine, as_primative_name<float>());
		registerEventGetParameter<EMP::Core::word>(engine, as_primative_name<EMP::Core::word>());
		//! \todo TODO: Perhaps these shouldn't be registered here - they rely on types that may not be registered
		//  perhaps: GetParameter<EMP::Core::Vector2i> could be registered in registerVector2<int>
		registerEventGetParameter<EMP::Core::Vector2i>(engine, "e_Vector2i");
		registerEventGetParameter<EMP::Core::Vector2f>(engine, "e_Vector2f");
		registerEventGetParameter<EMP::Core::String>(engine, "e_String");

		r = engine->RegisterObjectMethod("Event", "e_Dictionary &GetParameters()", asMETHOD(Rocket::Core::Event, GetParameters), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Event::GetParameters");

		r = engine->RegisterObjectMethod("Event", "void StopPropagation()", asMETHOD(Rocket::Core::Event, StopPropagation), asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register Event::StopPropagation");
	}

	void PropertyDictionaryCtor(Rocket::Core::PropertyDictionary *ptr)
	{
		new(ptr) Rocket::Core::PropertyDictionary();
	}

	void PropertyDictionaryDtor(Rocket::Core::PropertyDictionary *obj)
	{
		obj->~PropertyDictionary();
	}

	void registerPropertyDictionary(asIScriptEngine *engine)
	{
		int r;
		r = engine->RegisterObjectType("PropertyDictionary", sizeof(Rocket::Core::PropertyDictionary), asOBJ_VALUE | asOBJ_APP_CLASS_CD);
		if (r < 0)
			throw Exception("Couldn't register PropertyDictionary type");

		r = engine->RegisterObjectBehaviour("PropertyDictionary",
			asBEHAVE_CONSTRUCT,
			"void f()",
			asFUNCTION(PropertyDictionaryCtor),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register PropertyDictionary type");

		r = engine->RegisterObjectBehaviour("PropertyDictionary",
			asBEHAVE_DESTRUCT,
			"void f()",
			asFUNCTION(PropertyDictionaryDtor),
			asCALL_CDECL_OBJLAST);
		if (r < 0)
			throw Exception("Couldn't register PropertyDictionary type");

		r = engine->RegisterObjectMethod("PropertyDictionary",
			"const r_Property &GetProperty() const",
			asMETHOD(Rocket::Core::PropertyDictionary, GetProperty),
			asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register PropertyDictionary type");

		r = engine->RegisterObjectMethod("PropertyDictionary",
			"int GetNumProperties() const",
			asMETHOD(Rocket::Core::PropertyDictionary, GetNumProperties),
			asCALL_THISCALL);
		if (r < 0)
			throw Exception("Couldn't register PropertyDictionary type");
	}

}}}
