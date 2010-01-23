template <typename T>
void registerStlVector<T>(asIScriptEngine *engine, const std::string &script_name, const std::string &t_name)
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
	// init CTOR
	r = engine->RegisterObjectBehaviour(c_script_name,
		asBEHAVE_CONSTRUCT,
		"void f(uint)",
		asFUNCTION(registerStlVector_Util<T>::construct_init),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");
	// Copy CTOR
	r = engine->RegisterObjectBehaviour(c_script_name,
		asBEHAVE_CONSTRUCT,
		C_STR("void f(const " + script_name + " &in)"),
		asFUNCTION(registerStlVector_Util<T>::construct_copy),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");

	// Destruct
	r = engine->RegisterObjectBehaviour(c_script_name,
		asBEHAVE_DESTRUCT,
		"void f()",
		asFUNCTION(registerStlVector_Util<T>::destruct),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");

	// Assign
	r = engine->RegisterObjectMethod(c_script_name,
		(script_name + " &opAssign(const " + script_name + " &in)").c_str(),
		asMETHODPR(stl::vector<T>, operator=, (const stl::vector<T>&), stl::vector<T>&),
		asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");

	// Index
	r = engine->RegisterObjectBehaviour(c_script_name,
		asBEHAVE_INDEX,
		(t_name+"& f(int)").c_str(),
		asFUNCTION(registerStlVector_Util<T>::index),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");
	// Const index
	r = engine->RegisterObjectBehaviour(c_script_name,
		asBEHAVE_INDEX,
		("const "+t_name+"& f(int) const").c_str(),
		asFUNCTION(registerStlVector_Util<T>::index),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");

	// Methods
	// push_back
	r = engine->RegisterObjectMethod(c_script_name,
		("void push_back(const "+t_name+"&in)").c_str(),
		asFUNCTION(registerStlVector_Util<T>::push_back),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");

	// size
	r = engine->RegisterObjectMethod(c_script_name,
		"uint size() const",
		asFUNCTION(registerStlVector_Util<T>::size),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");
}

template <typename _Key>
void registerStlSet<_Key>(asIScriptEngine *engine, const std::string &script_name, const std::string &t_name)
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
void registerStlMap<_Key, _T>(asIScriptEngine *engine, const std::string &container_name, const std::string &key_name, const std::string &t_name)
{
	typedef registerStlMap_Util<_Key, _T> regUtil;

	const char *c_script_name = container_name.c_str();
	int r;
	r = engine->RegisterObjectType(c_script_name, sizeof(EMP::Core::STL::map<_Key,_T>), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
	if (r < 0)
		throw Exception("Couldn't register " + container_name + " type");

	// CTOR
	r = engine->RegisterObjectBehaviour(c_script_name,
		asBEHAVE_CONSTRUCT,
		"void f()",
		asFUNCTION(regUtil::construct),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + container_name + " ctor");
	//  Copy CTOR
	r = engine->RegisterObjectBehaviour(c_script_name,
		asBEHAVE_CONSTRUCT,
		C_STR("void f(const " + container_name + " &in)"),
		asFUNCTION(regUtil::construct_copy),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + container_name + " copy ctor");
	// Destruct
	r = engine->RegisterObjectBehaviour(c_script_name,
		asBEHAVE_DESTRUCT,
		"void f()",
		asFUNCTION(regUtil::destruct),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + container_name + " dtor");

	// Assign
	r = engine->RegisterObjectMethod(c_script_name,
		C_STR(container_name + " &opAssign(const " + container_name + " &in)"),
		asMETHODPR(regUtil::map_type, operator=, (const regUtil::map_type&), regUtil::map_type&),
		asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + container_name + " type");

	// Index
	r = engine->RegisterObjectBehaviour(c_script_name,
		asBEHAVE_INDEX,
		(t_name+"& f("+key_name+")").c_str(),
		asFUNCTION(regUtil::index),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + container_name + " type");
	// Const index
	r = engine->RegisterObjectBehaviour(c_script_name,
		asBEHAVE_INDEX,
		("const "+t_name+"& f("+key_name+") const").c_str(),
		asFUNCTION(regUtil::index),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + container_name + " type");

	// Methods
	// size
	r = engine->RegisterObjectMethod(c_script_name,
		"uint size() const",
		asFUNCTION(regUtil::size),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + container_name + " type");
}
