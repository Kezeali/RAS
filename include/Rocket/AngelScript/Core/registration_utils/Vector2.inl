// T is component (i.e. x, y) type
template <typename T>
void registerVector2(asIScriptEngine *engine, const std::string &script_name)
{
	registerVector2<T>(engine, script_name, as_primative_name<T>());
}

// T is component (i.e. x, y) type
template <typename T>
void registerVector2(asIScriptEngine *engine, const std::string &script_name, const std::string &T_name)
{
	static_assert(std::is_arithmetic<T>::value, "T must be an ");

	ROCKET_ASSERT(T_name != "");

	const char *c_script_name = script_name.c_str();
	int r;
	r = engine->RegisterObjectType(c_script_name, sizeof(Rocket::Core::Vector2<T>), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C);
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
		("void f(" + T_name + " x, " + T_name + " y)").c_str(),
		asFUNCTION(registerVector2_Utils<T>::construct_init),
		asCALL_CDECL_OBJLAST);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");

	r = engine->RegisterObjectProperty(c_script_name, (T_name + " x").c_str(), offsetof(Rocket::Core::Vector2<T>, x));
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");
	r = engine->RegisterObjectProperty(c_script_name, (T_name + " y").c_str(), offsetof(Rocket::Core::Vector2<T>, y));
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");
}
