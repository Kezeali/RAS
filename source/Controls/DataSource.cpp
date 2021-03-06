/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../../include/Rocket/AngelScript/Controls/DataSource.h"

#include "../../include/Rocket/AngelScript/Core/Exception.h"

#include <Rocket/Controls/DataSource.h>

#include <ScriptUtils/Inheritance/ScriptObjectWrapper.h>
#include <ScriptUtils/Calling/Caller.h>


namespace Rocket { namespace AngelScript {

	//! DataSource that calls script-object methods for it's implementation
	class ScriptedDataSource : public Rocket::Controls::DataSource, public ScriptUtils::Inheritance::ScriptObjectWrapper
	{
	public:
		//! CTOR
		ScriptedDataSource(asIScriptObject* self, const Rocket::Core::String &name);
		virtual ~ScriptedDataSource();

		//! DataSource#GetRow() implementation
		void GetRow(Rocket::Core::StringList& row, const Rocket::Core::String& table, int row_index, const Rocket::Core::StringList& columns);
		//! DataSource#GetNumRows() implementation
		int GetNumRows(const Rocket::Core::String& table);

		void* GetScriptObject() const;
	};

	ScriptedDataSource::ScriptedDataSource(asIScriptObject* self, const Rocket::Core::String &name)
		: Rocket::Controls::DataSource(name),
		ScriptUtils::Inheritance::ScriptObjectWrapper(self, "IDataSource")
	{
	}

	ScriptedDataSource::~ScriptedDataSource()
	{
	}

	void ScriptedDataSource::GetRow(Rocket::Core::StringList &row, const Rocket::Core::String &table, int row_index, const Rocket::Core::StringList &columns)
	{
		ScriptUtils::Calling::Caller f = this->get_caller("void GetRow(StringList&out, const String&in, int, const StringList&in)");
		if (f)
		{
			f(&row, &table, row_index, &columns);
		}
	}

	int ScriptedDataSource::GetNumRows(const Rocket::Core::String &table)
	{
		ScriptUtils::Calling::Caller f = this->get_caller("int GetNumRows(const String&in)");
		if (f)
		{
			return *static_cast<int*>( f(&table) );
		}
		return 0;
	}

	void* ScriptedDataSource::GetScriptObject() const
	{
		return static_cast<void*>( _obj );
		//return NULL;
	}

	void RegisterDataSourceInterface(asIScriptEngine *engine)
	{
		int r = engine->RegisterInterface("IDataSource");
		if (r < 0)
			throw Exception("Couldn't register IDataSource");
		r = engine->RegisterInterfaceMethod("IDataSource", "void GetRow(StringList&out, const String&in, int, const StringList&in)");
		if (r < 0)
			throw Exception("Couldn't register IDataSource");
		r = engine->RegisterInterfaceMethod("IDataSource", "int GetNumRows(const String&in)");
		if (r < 0)
			throw Exception("Couldn't register IDataSource");
	}

	void CreateDataSource(const Rocket::Core::String &name, asIScriptObject *data_interface)
	{
		new ScriptedDataSource(data_interface, name);
		data_interface->Release();
	}

	void DestroyDataSource(const Rocket::Core::String &name)
	{
		Rocket::Controls::DataSource *dataSource = Rocket::Controls::DataSource::GetDataSource(name);
		// Check that a valid ScriptDataSource was returned
		if (dataSource != NULL && dataSource->GetScriptObject() != NULL)
			delete dataSource;
	}

	void RegisterDataSourceCreator(asIScriptEngine *engine)
	{
		int r;
		r = engine->RegisterGlobalFunction("void AddDataSource(const String &in, IDataSource@)",
			asFUNCTION(CreateDataSource), asCALL_CDECL);
		if (r < 0)
			throw Exception("Couldn't register AddDataSource(name, datasource)");

		r = engine->RegisterGlobalFunction("void RemoveDataSource(const String &in)",
			asFUNCTION(DestroyDataSource), asCALL_CDECL);
		if (r < 0)
			throw Exception("Couldn't register RemoveDataSource(name)");
	}

	void RegisterDataSource(asIScriptEngine *engine)
	{
		RegisterDataSourceInterface(engine);
		RegisterDataSourceCreator(engine);
	}

}}
