/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_REGISTRATIONUTILS_STL
#define H_ROCKET_AS_REGISTRATIONUTILS_STL

#include <map>
#include <set>
#include <vector>
#include <angelscript.h>

#include "../Exception.h"


namespace Rocket { namespace AngelScript { namespace _registration_utils {

	//! Registers a EMP#Core#STL#vector type
	template <typename T>
	static void registerStlVector(asIScriptEngine *engine, const std::string &containter_typename, const std::string &T_typename);

	//! Registers a EMP#Core#STL#set type
	template <typename _Key>
	static void registerStlSet(asIScriptEngine *engine, const std::string &containter_typename, const std::string &Key_typename);

	//! Registers a EMP#Core#STL#map type
	template <typename _Key, typename _T>
	static void registerStlMap(asIScriptEngine *engine, const std::string &containter_typename, const std::string &Key_typename, const std::string &T_typename);

	template <typename T>
	struct registerStlVector_Util
	{
		typedef std::vector<T> vector_type;
		typedef typename vector_type::size_type size_type;

		static void construct(vector_type *ptr)
		{
			new(ptr) vector_type();
		}

		static void construct_init(size_type size, vector_type *ptr)
		{
			new(ptr) vector_type(size);
		}

		static void construct_copy(const vector_type &copy, vector_type *ptr)
		{
			new(ptr) vector_type(copy);
		}

		static void destruct(vector_type *ptr)
		{
			ptr->~vector_type();
		}

		static T* index(size_type i, vector_type *obj)
		{
			if (i < 0 || i >= obj->size())
			{
				asIScriptContext* context = asGetActiveContext();
				if( context )
					context->SetException("Vector index out of bounds.");
				return NULL;
			}

			return &(*obj)[i];
		}

		static size_type size(vector_type *obj)
		{
			return obj->size();
		}

		static void push_back(const T &item, vector_type *obj)
		{
			obj->push_back(item);
		}
	};

	template <typename _Key, typename _T>
	struct registerStlMap_Util
	{
		typedef std::map<_Key, _T> map_type;
		typedef typename map_type::size_type size_type;

		static void construct(map_type *ptr)
		{
			new(ptr) map_type();
		}

		static void construct_copy(const map_type &copy, map_type *ptr)
		{
			new(ptr) map_type(copy);
		}

		static void destruct(map_type *ptr)
		{
			ptr->~map_type();
		}

		static _T* index(_Key key, map_type *obj)
		{
			return &(*obj)[key];
		}

		static size_type size(map_type *obj)
		{
			return obj->size();
		}
	};

#include "EMPSTL.inl"

}}}

#endif
