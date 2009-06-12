template <typename T>
void registerStlVector<T>(asIScriptEngine *engine, const std::string &script_name, const std::string &T_name)
{
	typedef typename stl::vector<T>::size_type size_type;

	const char *c_script_name = script_name.c_str();
	int r;
	r = engine->RegisterObjectType(c_script_name, sizeof(stl::vector<T>), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");

	// CTOR
	r = engine->RegisterObjectBehaviour(c_script_name,
		asBEHAVE_CONSTRUCT,
		"void f()",
		asFUNCTION(registerStlVector_Util<T>::construct),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " ctor");

	r = engine->RegisterObjectBehaviour(c_script_name,
		asBEHAVE_CONSTRUCT,
		"void f(uint)",
		asFUNCTION(registerStlVector_Util<T>::construct_init),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");
	//  Copy CTOR
	r = engine->RegisterObjectBehaviour(c_script_name,
		asBEHAVE_CONSTRUCT,
		C_STR("void f(const " + script_name + " &in)"),
		asFUNCTION(registerStlVector_Util<T>::construct_copy),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");

	r = engine->RegisterObjectBehaviour(c_script_name,
		asBEHAVE_DESTRUCT,
		"void f()",
		asFUNCTION(registerStlVector_Util<T>::destruct),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");

	r = engine->RegisterObjectBehaviour(c_script_name,
		asBEHAVE_ASSIGNMENT,
		(script_name + " &f(const " + script_name + " &in)").c_str(),
		asMETHODPR(stl::vector<T>, operator=, (const stl::vector<T>&), stl::vector<T>&),
		asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");

	r = engine->RegisterObjectBehaviour(c_script_name,
		asBEHAVE_INDEX,
		(T_name+"& f(int)").c_str(),
		asFUNCTION(registerStlVector_Util<T>::index),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");

	r = engine->RegisterObjectBehaviour(c_script_name,
		asBEHAVE_INDEX,
		("const "+T_name+"& f(int) const").c_str(),
		asFUNCTION(registerStlVector_Util<T>::index),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");
}

template <typename _Key>
void registerStlSet<_Key>(asIScriptEngine *engine, const std::string &script_name, const std::string &T_name)
{
	const char *c_script_name = script_name.c_str();
	int r;
	r = engine->RegisterObjectType(c_script_name, sizeof(EMP::Core::STL::set<_Key>), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");

	//// CTOR
	//r = engine->RegisterObjectBehaviour(c_script_name,
	//	asBEHAVE_CONSTRUCT,
	//	"void f()",
	//	asFUNCTION(registerStlVector_Util<T>::construct),
	//	asCALL_CDECL_OBJLAST);
	//if (r < 0)
	//	throw Exception("Couldn't register " + script_name + " ctor");

	//r = engine->RegisterObjectBehaviour(c_script_name,
	//	asBEHAVE_CONSTRUCT,
	//	"void f(uint)",
	//	asFUNCTIONPR(registerStlVector_Util<T>::construct_init, (EMP::Core::STL::vector<t>::size_type), void),
	//	asCALL_CDECL_OBJLAST);
	//if (r < 0)
	//	throw Exception("Couldn't register " + script_name + " type");
	////  Copy CTOR
	//r = engine->RegisterObjectBehaviour(c_script_name,
	//	asBEHAVE_CONSTRUCT,
	//	C_STR("void f(const " + script_name + " &in)"),
	//	asFUNCTIONPR(registerStlVector_Util<T>::construct_init, (const EMP::Core::STL::vector<t> &), void),
	//	asCALL_CDECL_OBJLAST);
	//if (r < 0)
	//	throw Exception("Couldn't register " + script_name + " type");

	//r = engine->RegisterObjectBehaviour(c_script_name,
	//	asBEHAVE_DESTRUCT,
	//	"void f()",
	//	asFUNCTION(registerStlVector_Util<T>::destruct),
	//	asCALL_CDECL_OBJLAST);
	//if (r < 0)
	//	throw Exception("Couldn't register " + script_name + " type");

	//r = engine->RegisterObjectBehaviour(c_script_name,
	//	asBEHAVE_ASSIGNMENT,
	//	C_STR(script_name + " &f(const " + script_name + " &in)"),
	//	asMETHODPR(T, operator=, (const T&), T&),
	//	asCALL_THISCALL);
	//if (r < 0)
	//	throw Exception("Couldn't register " + script_name + " type");

	//r = engine->RegisterObjectBehaviour(V_AS.c_str(),
	//	asBEHAVE_INDEX,
	//	(T_AS+"& f(int)").c_str(),
	//	asFUNCTION(registerStlVector_Util<T>::index),
	//	asCALL_CDECL_OBJLAST);
	//if (r < 0)
	//	throw Exception("Couldn't register " + script_name + " type");

	//r = engine->RegisterObjectBehaviour(V_AS.c_str(),
	//	asBEHAVE_INDEX,
	//	("const "+T_AS+"& f(int) const").c_str(),
	//	asFUNCTION(registerStlVector_Util<T>::index),
	//	asCALL_CDECL_OBJLAST);
	//if (r < 0)
	//	throw Exception("Couldn't register " + script_name + " type");
}

template <typename _Key, typename _T>
void registerStlMap<_Key, _T>(asIScriptEngine *engine, const std::string &script_name, const std::string &T_name)
{
	const char *c_script_name = script_name.c_str();
	int r;
	r = engine->RegisterObjectType(c_script_name, sizeof(EMP::Core::STL::map<_Key, _T>), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");

	//// CTOR
	//r = engine->RegisterObjectBehaviour(c_script_name,
	//	asBEHAVE_CONSTRUCT,
	//	"void f()",
	//	asFUNCTION(registerStlVector_Util<T>::construct),
	//	asCALL_CDECL_OBJLAST);
	//if (r < 0)
	//	throw Exception("Couldn't register " + script_name + " ctor");

	//r = engine->RegisterObjectBehaviour(c_script_name,
	//	asBEHAVE_CONSTRUCT,
	//	"void f(uint)",
	//	asFUNCTIONPR(registerStlVector_Util<T>::construct_init, (EMP::Core::STL::vector<t>::size_type), void),
	//	asCALL_CDECL_OBJLAST);
	//if (r < 0)
	//	throw Exception("Couldn't register " + script_name + " type");
	////  Copy CTOR
	//r = engine->RegisterObjectBehaviour(c_script_name,
	//	asBEHAVE_CONSTRUCT,
	//	C_STR("void f(const " + script_name + " &in)"),
	//	asFUNCTIONPR(registerStlVector_Util<T>::construct_init, (const EMP::Core::STL::vector<t> &), void),
	//	asCALL_CDECL_OBJLAST);
	//if (r < 0)
	//	throw Exception("Couldn't register " + script_name + " type");

	//r = engine->RegisterObjectBehaviour(c_script_name,
	//	asBEHAVE_DESTRUCT,
	//	"void f()",
	//	asFUNCTION(registerStlVector_Util<T>::destruct),
	//	asCALL_CDECL_OBJLAST);
	//if (r < 0)
	//	throw Exception("Couldn't register " + script_name + " type");

	//r = engine->RegisterObjectBehaviour(c_script_name,
	//	asBEHAVE_ASSIGNMENT,
	//	C_STR(script_name + " &f(const " + script_name + " &in)"),
	//	asMETHODPR(T, operator=, (const T&), T&),
	//	asCALL_THISCALL);
	//if (r < 0)
	//	throw Exception("Couldn't register " + script_name + " type");

	//r = engine->RegisterObjectBehaviour(V_AS.c_str(),
	//	asBEHAVE_INDEX,
	//	(T_AS+"& f(int)").c_str(),
	//	asFUNCTION(registerStlVector_Util<T>::index),
	//	asCALL_CDECL_OBJLAST);
	//if (r < 0)
	//	throw Exception("Couldn't register " + script_name + " type");

	//r = engine->RegisterObjectBehaviour(V_AS.c_str(),
	//	asBEHAVE_INDEX,
	//	("const "+T_AS+"& f(int) const").c_str(),
	//	asFUNCTION(registerStlVector_Util<T>::index),
	//	asCALL_CDECL_OBJLAST);
	//if (r < 0)
	//	throw Exception("Couldn't register " + script_name + " type");
}
