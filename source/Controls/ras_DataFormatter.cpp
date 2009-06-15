/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../include/Rocket/AngelScript/Controls/ras_DataFormatter.h"

#include "../include/Rocket/AngelScript/Core/ras_Exception.h"

#include <Rocket/Controls/DataFormatter.h>

#include <Inheritance/ScriptObjectWrapper.h>
#include <Calling/Caller.h>


namespace Rocket { namespace AngelScript {

	//! DataFormatter that calls script-object methods for it's implementation
	class ScriptedDataFormatter : public Rocket::Controls::DataFormatter, public ScriptUtils::Inheritance::ScriptObjectWrapper
	{
	public:
		//! CTOR
		ScriptedDataFormatter(asIScriptObject* self, const EMP::Core::String &name);

		//! Returns formatted data
		void FormatData(EMP::Core::String& formatted_data, const EMP::Core::StringList& raw_data);

		void* GetScriptObject() const;
	};

	ScriptedDataFormatter::ScriptedDataFormatter(asIScriptObject* self, const EMP::Core::String &name)
		: Rocket::Controls::DataFormatter(name),
		ScriptUtils::Inheritance::ScriptObjectWrapper(self, "IDataFormatter")
	{
	}

	void ScriptedDataFormatter::FormatData(EMP::Core::String& formatted_data, const EMP::Core::StringList& raw_data)
	{
		ScriptUtils::Calling::Caller f = this->get_caller("e_String FormatData(const StringList&in)");
		if (f.ok())
		{
			//EMP::Core::String comma_seperated_data;
			//EMP::Core::StringUtilities::JoinString(comma_seperated_data, raw_data);
			//formatted_data = *static_cast<EMP::Core::String*>( f(&comma_seperated_data) );
			formatted_data = *static_cast<EMP::Core::String*>( f(&raw_data) );
		}
	}

	void* ScriptedDataFormatter::GetScriptObject() const
	{
		return static_cast<void*>( _obj );
		//return NULL;
	}

	void RegisterDataFormatterInterface(asIScriptEngine *engine)
	{
		int r = engine->RegisterInterface("IDataFormatter");
		if (r < 0)
			throw Exception("Couldn't register IDataFormatter");
		r = engine->RegisterInterfaceMethod("IDataFormatter", "e_String FormatData(const StringList&in)");
		if (r < 0)
			throw Exception("Couldn't register IDataFormatter");
	}

	void CreateDataFormatter(const EMP::Core::String &name, asIScriptObject *formatter_interface)
	{
		new ScriptedDataFormatter(formatter_interface, name);
		formatter_interface->Release();
	}

	void DestroyDataFormatter(const EMP::Core::String &name)
	{
		Rocket::Controls::DataFormatter *dataFormatter = Rocket::Controls::DataFormatter::GetDataFormatter(name);
		// Check that a valid ScriptedDataFormatter was returned
		if (dataFormatter != NULL && dataFormatter->GetScriptObject() != NULL)
			delete dataFormatter;
	}

	void RegisterDataFormatterCreator(asIScriptEngine *engine)
	{
		int r;
		r = engine->RegisterGlobalFunction("void AddDataFormatter(const e_String &in, IDataFormatter@)",
			asFUNCTION(CreateDataFormatter), asCALL_CDECL);
		if (r < 0)
			throw Exception("Couldn't register AddDataFormatter(name, datasource)");

		r = engine->RegisterGlobalFunction("void RemoveDataFormatter(const e_String &in)",
			asFUNCTION(DestroyDataFormatter), asCALL_CDECL);
		if (r < 0)
			throw Exception("Couldn't register RemoveDataFormatter(name)");
	}

	void RegisterDataFormatter(asIScriptEngine *engine)
	{
		RegisterDataFormatterInterface(engine);
		RegisterDataFormatterCreator(engine);
	}

}}
