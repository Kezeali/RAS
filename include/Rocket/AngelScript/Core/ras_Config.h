#ifndef H_ROCKET_AS_CONFIG
#define H_ROCKET_AS_CONFIG

#include <EMP/Core/Platform.h>


#if defined EMP_PLATFORM_WIN32 && defined _USRDLL

#ifdef RASCOREDLL_EXPORTS
#define RASCOREDLL_API __declspec(dllexport)
#else
#define RASCOREDLL_API __declspec(dllimport)
#endif

#else

#define RASCOREDLL_API

#endif

#endif