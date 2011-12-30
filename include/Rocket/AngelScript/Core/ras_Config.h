#ifndef H_ROCKET_AS_CONFIG
#define H_ROCKET_AS_CONFIG

#include <Rocket/Core/Platform.h>


#if !defined RAS_STATIC_LIB

#if defined ROCKET_PLATFORM_WIN32 && defined _USRDLL

#ifdef RASCOREDLL_EXPORTS
#define RASCOREDLL_API __declspec(dllexport)
#else
#define RASCOREDLL_API __declspec(dllimport)
#endif

#else // Not win32 dll
#define RASCOREDLL_API// __attribute__((visibility("default")))
#endif

#else // RAS_STATIC_LIB

#define RASCOREDLL_API

#endif

#endif
