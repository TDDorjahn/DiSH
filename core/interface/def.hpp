#pragma once

#if defined(NDEBUG)
    #define SHELL_DEBUG 1
#endif

#ifndef SHELL_DEBUG
    #define SHELL_DEBUG 0
#endif

#define SHELL_BUILD_DATE __DATE__
#define SHELL_BUILD_TIME __TIME__

#define SHELL_VERSION_MAJOR 0
#define SHELL_VERSION_MINOR 0
#define SHELL_VERSION_PATCH 1

#ifndef SHELL_ASSERT
    #include <cassert>
    #define SHELL_ASSERT(expr) assert(expr)
#endif

#define SHELL_VERSION_FORMAT_BRACED 0                               // Brace Format: {0,0,1}
#define SHELL_VERSION_FORMAT_SQUARE 1                               // Square Format: [0,0,1]
#define SHELL_VERSION_FORMAT_PARENTHESES 2                          // Parantheses Format: (0,0,1)
#define SHELL_VERSION_FORMAT_SPACED 3                               // Spaced Format: 0 0 1
#define SHELL_VERSION_FORMAT_UNDER 4                                // Under Format: 0_0_1
#define SHELL_VERSION_FORMAT_SEMANTIC 5                             // Semantic: 0.0.1
#define SHELL_VERSION_FORMAT_DEFAULT SHELL_VERSION_FORMAT_SEMANTIC  // Default: 0.0.1

#define SHELL_SQUARE_CHAR_OPEN "["
#define SHELL_SQUARE_CHAR_CLOSE "]"
#define SHELL_PAREN_CHAR_OPEN "("
#define SHELL_PAREN_CHAR_CLOSE ")"
#define SHELL_BRACE_CHAR_OPEN "{"
#define SHELL_BRACE_CHAR_CLOSE "}"
#define SHELL_CHAR_SPACE " "