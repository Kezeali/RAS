/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../../include/Rocket/AngelScript/Controls/ras_DataFormatter.h"

#include "../../include/Rocket/AngelScript/Core/ras_Exception.h"

#include <Rocket/Controls/DataFormatter.h>

#include <ScriptUtils/Inheritance/ScriptObjectWrapper.h>
#include <ScriptUtils/Calling/Caller.h>


namespace Rocket { namespace AngelScript {

	//! DataFormatter that calls script-object methods for it's implementation
	class ScriptedDataFormatter : public Rocket::Controls::DataFormatter, public ScriptUtils::Inheritance::ScriptObjectWrapper
	{
	public:
		//! CTOR
		ScriptedDataFormatter(asIScriptObject* self, const Rocket::Core::String &name);

		//! Returns formatted data
		void FormatData(Rocket::Core::String& formatted_data, const Rocket::Core::StringList& raw_data);

		void* GetScriptObject() const;
	};

	ScriptedDataFormatter::ScriptedDataFormatter(asIScriptObject* self, const Rocket::Core::String &name)
		: Rocket::Controls::DataFormatter(name),
		ScriptUtils::Inheritance::ScriptObjectWrapper(self, "IDataFormatter")
	{
	}

	void ScriptedDataFormatter::FormatData(Rocket::Core::String& formatted_data, const Rocket::Core::StringList& raw_data)
	{
		ScriptUtils::Calling::Caller f = this->get_caller("rString FormatData(const StringList&in)");
		if (f)
		{
			//Rocket::Core::String comma_seperated_data;
			//Rocket::Core::StringUtilities::JoinString(comma_seperated_data, raw_data);
			//formatted_data = *static_cast<Rocket::Core::String*>( f(&comma_seperated_data) );
			formatted_data = *static_cast<Rocket::Core::String*>( f(&raw_data) );
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
		r = engine->RegisterInterfaceMethod("IDataFormatter", "rString FormatData(const StringList&in)");
		if (r < 0)
			throw Exception("Couldn't register IDataFormatter");
	}

	void CreateDataFormatter(const Rocket::Core::String &name, asIScriptObject *formatter_interface)
	{
		new ScriptedDataFormatter(formatter_interface, name);
		formatter_interface->Release();
	}

	void DestroyDataFormatter(const Rocket::Core::String &name)
	{
		Rocket::Controls::DataFormatter *dataFormatter = Rocket::Controls::DataFormatter::GetDataFormatter(name);
		// Check that a valid ScriptedDataFormatter was returned
		if (dataFormatter != NULL && dataFormatter->GetScriptObject() != NULL)
			delete dataFormatter;
	}

	void RegisterDataFormatterCreator(asIScriptEngine *engine)
	{
		int r;
		r = engine->RegisterGlobalFunction("void AddDataFormatter(const rString &in, IDataFormatter@)",
			asFUNCTION(CreateDataFormatter), asCALL_CDECL);
		if (r < 0)
			throw Exception("Couldn't register AddDataFormatter(name, datasource)");

		r = engine->RegisterGlobalFunction("void RemoveDataFormatter(const rString &in)",
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
