// T is component (i.e. x, y) type
template <typename T>
void registerVector2<T>(asIScriptEngine *engine, const std::string &script_name)
{
	registerVector2<T>(engine, script_name, as_primative_name<T>());
}

// T is component (i.e. x, y) type
template <typename T>
void registerVector2<T>(asIScriptEngine *engine, const std::string &script_name, const std::string &T_name)
{
	BOOST_MPL_ASSERT(( std::tr1::is_fundamental<T> ));

	EMP_ASSERT(T_name != "");

	const char *c_script_name = script_name.c_str();
	int r;
	r = engine->RegisterObjectType(c_script_name, sizeof(EMP::Core::Vector2<T>), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");

	// CTOR
	r = engine->RegisterObjectBehaviour(c_script_name,
		asBEHAVE_CONSTRUCT,
		"void f()",
		asFUNCTION(registerVector2_Utils<T>::construct),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");

	r = engine->RegisterObjectBehaviour(c_script_name,
		asBEHAVE_CONSTRUCT,
		C_STR("void f(" + T_name + " x, " + T_name + " y)"),
		asFUNCTION(registerVector2_Utils<T>::construct_init),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");

	/*engine->RegisterObjectBehaviour(c_script_name,
	asBEHAVE_ASSIGNMENT,
	"e_" + script_name + " &f(e_" + script_name + " &in)",
	asMETHODPR(EMP::Core::" + script_name + ", operator=, (const EMP::Core::" + script_name + "&), EMP::Core::" + script_name + "&),
	asCALL_THISCALL);*/

	r = engine->RegisterObjectProperty(c_script_name, C_STR(T_name + " x"), offsetof(EMP::Core::Vector2<T>, x));
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");
	r = engine->RegisterObjectProperty(c_script_name, C_STR(T_name + " y"), offsetof(EMP::Core::Vector2<T>, y));
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");
}
