#pragma once

#if defined(__linux__) || defined(linux) || defined(__linux) || defined(__gnu_linux__)
    #define DSH_LINUX
#endif

#if defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
    #define DSH_WIN
#endif

#if defined(macintosh) || defined(Macintosh) || defined(__APPLE__) || defined(__MACH__)
    #define DSH_MOS
#endif