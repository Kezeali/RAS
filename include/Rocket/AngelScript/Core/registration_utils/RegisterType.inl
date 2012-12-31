// ReferenceCountable derived types
template <typename T>
inline void referenceCountable(asIScriptEngine *engine, const std::string &script_name)
{
	// Make sure the given type is derived from ReferenceCountable
	static_assert(std::is_base_of<Rocket::Core::ReferenceCountable, T>::value, "This is for registering ReferenceCountable derived types");

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

inline void interface(asIScriptEngine *engine, const std::string &script_name)
{
	const char *c_script_name = script_name.c_str();
	int r;
	r = engine->RegisterInterface(c_script_name);
	if (r < 0)
		throw Exception("Couldn't register " + script_name + " interface");
}
