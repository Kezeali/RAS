/*
* libRocket AngleScript binding
* By Elliot Hayward
*/

#ifndef H_ROCKET_AS_REGISTRATIONUTILS_STL
#define H_ROCKET_AS_REGISTRATIONUTILS_STL

#include <EMP/Core/STL/map>
#include <EMP/Core/STL/set>
#include <EMP/Core/STL/vector>
#include <angelscript.h>

#include "../ras_Exception.h"

#include <vector>


namespace Rocket { namespace AngelScript { namespace _registration_utils {

	namespace stl = EMP::Core::STL;

	//! Registers a EMP#Core#STL#vector type
	template <typename T>
	static void registerStlVector(asIScriptEngine *engine, const std::string &containter_typename, const std::string &T_typename);

	//! Registers a EMP#Core#STL#set type
	template <typename _Key>
	static void registerStlSet(asIScriptEngine *engine, const std::string &containter_typename, const std::string &T_typename);

	//! Registers a EMP#Core#STL#map type
	template <typename _Key, typename _T>
	static void registerStlMap(asIScriptEngine *engine, const std::string &containter_typename, const std::string &T_typename);

	template <typename T>
	struct registerStlVector_Util
	{
		typedef EMP::Core::STL::vector<T> vector_type;
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
	};

#include "ras_EMPSTL.inl"

}}}

#endif
