#ifndef H_ROCKET_AS_CONTROLS_CONFIG
#define H_ROCKET_AS_CONTROLS_CONFIG

#include <EMP/Core/Platform.h>


#if defined EMP_PLATFORM_WIN32 && defined _USRDLL

#ifdef RASCONTROLSDLL_EXPORTS
#define RASCONTROLSDLL_API __declspec(dllexport)
#else
#define RASCONTROLSDLL_API __declspec(dllimport)
#endif

#else

#define RASCONTROLSDLL_API

#endif

#endif