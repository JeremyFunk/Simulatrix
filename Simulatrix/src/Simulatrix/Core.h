#pragma once

#ifdef SIMMAT_PLATFORM_WINDOWS
    #ifdef SIMMAT_BUILD_DLL
        #define SIMMAT_API __declspec(dllexport)
    #else
        #define SIMMAT_API __declspec(dllimport)
    #endif
#else
#error Only Windows supported!
#endif