#ifndef H_ROCKET_AS_CONFIG
#define H_ROCKET_AS_CONFIG

#include <Rocket/Core/Platform.h>


#if defined ROCKET_PLATFORM_WIN32 && defined _USRDLL

#ifdef RASCOREDLL_EXPORTS
#define RASCOREDLL_API __declspec(dllexport)
#else
#define RASCOREDLL_API __declspec(dllimport)
#endif

#else

#define RASCOREDLL_API

#endif

#endif