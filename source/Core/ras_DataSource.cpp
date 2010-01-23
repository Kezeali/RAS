/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#include "../include/Rocket/AngelScript/Core/ras_DataSource.h"

#include "../include/Rocket/AngelScript/Core/ras_Exception.h"

#include <EMP/Core/DataSource.h>

#include <ScriptUtils/Inheritance/ScriptObjectWrapper.h>
#include <ScriptUtils/Calling/Caller.h>


namespace Rocket { namespace AngelScript {

	//! DataSource that calls script-object methods for it's implementation
	class ScriptedDataSource : public EMP::Core::DataSource, public ScriptUtils::Inheritance::ScriptObjectWrapper
	{
	public:
		//! CTOR
		ScriptedDataSource(asIScriptObject* self, const EMP::Core::String &name);

		//! DataSource#GetRow() implementation
		void GetRow(EMP::Core::StringList& row, const EMP::Core::String& table, int row_index, const EMP::Core::StringList& columns);
		//! DataSource#GetNumRows() implementation
		int GetNumRows(const EMP::Core::String& table);

		void* GetScriptObject() const;
	};

	ScriptedDataSource::ScriptedDataSource(asIScriptObject* self, const EMP::Core::String &name)
		: EMP::Core::DataSource(name),
		ScriptUtils::Inheritance::ScriptObjectWrapper(self, "IDataSource")
	{
	}

	void ScriptedDataSource::GetRow(EMP::Core::StringList &row, const EMP::Core::String &table, int row_index, const EMP::Core::StringList &columns)
	{
		ScriptUtils::Calling::Caller f = this->get_caller("void GetRow(StringList&out, const e_String&in, int, const StringList&in)");
		if (f.ok())
		{
			f(&row, &table, row_index, &columns);
		}
	}

	int ScriptedDataSource::GetNumRows(const EMP::Core::String &table)
	{
		ScriptUtils::Calling::Caller f = this->get_caller("int GetNumRows(const e_String&in)");
		if (f.ok())
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
		r = engine->RegisterInterfaceMethod("IDataSource", "void GetRow(StringList&out, const e_String&in, int, const StringList&in)");
		if (r < 0)
			throw Exception("Couldn't register IDataSource");
		r = engine->RegisterInterfaceMethod("IDataSource", "int GetNumRows(const e_String&in)");
		if (r < 0)
			throw Exception("Couldn't register IDataSource");
	}

	void CreateDataSource(const EMP::Core::String &name, asIScriptObject *data_interface)
	{
		new ScriptedDataSource(data_interface, name);
		data_interface->Release();
	}

	void DestroyDataSource(const EMP::Core::String &name)
	{
		EMP::Core::DataSource *dataSource = EMP::Core::DataSource::GetDataSource(name);
		// Check that a valid ScriptDataSource was returned
		if (dataSource != NULL && dataSource->GetScriptObject() != NULL)
			delete dataSource;
	}

	void RegisterDataSourceCreator(asIScriptEngine *engine)
	{
		int r;
		r = engine->RegisterGlobalFunction("void AddDataSource(const e_String &in, IDataSource@)",
			asFUNCTION(CreateDataSource), asCALL_CDECL);
		if (r < 0)
			throw Exception("Couldn't register AddDataSource(name, datasource)");

		r = engine->RegisterGlobalFunction("void RemoveDataSource(const e_String &in)",
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
