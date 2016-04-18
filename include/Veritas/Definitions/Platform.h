#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #define PLATORM_WINDOWS PLATORM_WINDOWS
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
        #define PLATORM_IOS PLATORM_IOS
    #elif TARGET_OS_MAC
        #define PLATFORM_MACOS PLATFORM_MACOS
    #endif
#elif defined(__ANDROID__)
    #define PLATFORM_ANDROID PLATFORM_ANDROID
#elif defined(EMSCRIPTEN)
    #define PLATFORM_EMSCRIPTEN
#elif defined(__linux)
    #define PLATFORM_LINUX PLATFORM_LINUX
#endif

#ifdef __unix
    #define PLATFORM_UNIX PLATFORM_UNIX
#endif

#if defined(PLATFORM_ANDROID) || defined(PLATFORM_IOS)
    #define PLATFORM_MOBILE
#elif defined(PLATFORM_WINDOWS) || defined(PLATFORM_MACOS) || defined(PLATFORM_LINUX)
    #define PLATFORM_DESKTOP
#elif defined(JAVASCRIPT)
    #define PLATFORM_BROWSER
#endif

#if defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS) || defined(PLATFORM_ANDROID)
    #define PLATFORM_POSIX
#endif
