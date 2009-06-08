// ReferenceCountable derived types
template <typename T>
void referenceCountable<T>(asIScriptEngine *engine, const std::string &script_name)
{
	// Make sure the given type is derived from ReferenceCountable
	BOOST_MPL_ASSERT(( std::tr1::is_base_of<EMP::Core::ReferenceCountable, T> ));

	const char *c_script_name = script_name.c_str();
	int r;
	r = engine->RegisterObjectType(c_script_name, 0, asOBJ_REF);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");

	// AddReference / RemoveReference
	r = engine->RegisterObjectBehaviour(c_script_name, asBEHAVE_ADDREF, "void f()", asMETHOD(T, AddReference), asCALL_THISCALL);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");
	r = engine->RegisterObjectBehaviour(c_script_name, asBEHAVE_RELEASE, "void f()", asMETHOD(T, RemoveReference), asCALL_THISCALL); 
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " type");
}

template <typename T>
void interface<T>(asIScriptEngine *engine, const std::string &script_name)
{
	// Make sure the given type is abstract
	BOOST_MPL_ASSERT(( std::tr1::is_abstract<T> ));

	const char *c_script_name = script_name.c_str();
	int r;
	r = engine->RegisterInterface(c_script_name);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " interface");
}
