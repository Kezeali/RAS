template <typename T>
void registerStlVector(asIScriptEngine *engine, const std::string &script_name, const std::string &t_name)
{
	typedef typename std::vector<T>::size_type size_type;

	const char *c_script_name = script_name.c_str();
	int r;
	r = engine->RegisterObjectType(c_script_name, sizeof(std::vector<T>), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
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
		("void f(const " + script_name + " &in)").c_str(),
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
		asMETHODPR(std::vector<T>, operator=, (const std::vector<T>&), std::vector<T>&),
		asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");

	// Index
	r = engine->RegisterObjectMethod(c_script_name,
		(t_name+"& opIndex(uint)").c_str(),
		asFUNCTION(registerStlVector_Util<T>::index),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");
	// Const index
	r = engine->RegisterObjectMethod(c_script_name,
		("const "+t_name+"& opIndex(uint) const").c_str(),
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

template <typename _Key, typename _T>
void registerStlMap(asIScriptEngine *engine, const std::string &container_name, const std::string &key_name, const std::string &t_name)
{
	typedef registerStlMap_Util<_Key, _T> regUtil;
	typedef typename regUtil::map_type map_type;

	const char *c_script_name = container_name.c_str();
	int r;
	r = engine->RegisterObjectType(c_script_name, sizeof(std::map<_Key,_T>), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
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
		("void f(const " + container_name + " &in)").c_str(),
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
		(container_name + " &opAssign(const " + container_name + " &in)").c_str(),
		asMETHODPR(map_type, operator=, (const map_type&), map_type&),
		asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + container_name + " type");

	// Index
	r = engine->RegisterObjectMethod(c_script_name,
		(t_name+"& opIndex("+key_name+")").c_str(),
		asFUNCTION(regUtil::index),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + container_name + " type");
	// Const index
	r = engine->RegisterObjectMethod(c_script_name,
		("const "+t_name+"& opIndex("+key_name+") const").c_str(),
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
