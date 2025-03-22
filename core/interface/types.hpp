#pragma once

#include <string> //string, word
#include <string_view> //const_word, string_view
#include <vector> //lists, indices, word_list, word_ref_list, const_word_list
#include <cstdint> //int, uint, ptr, void types
#include <map> //format_map
#include <iterator> //iterator types

#if  defined(__linux__) || defined(__GNUC__) || defined(__APPLE__)
    #include <unistd.h>
    
    #ifdef __SIZEOF_FLOAT128__
        #include <quadmath.h>
    #endif

#else
    #include <windows.h>
#endif

#include "cpudef.hpp"
#include "def.hpp"
#include "struct_types.hpp"

namespace dsh {

    template<typename Float>
    struct _Select_Quad_Type { using type = long double; };

    #ifdef DSH_FLOAT128
    template <>
    struct _Select_Quad_Type<void> { using type = __float128; };
    #endif

    using c8 = char;
    using c16 = char16_t; //Default behavior is unsigned int
    using c8_c = c8 const;
    using c16_c = c16 const; //Default behavior is unsigned int

    using uc8 = unsigned c8;
    using uc16 = c16; //Default behavior is unsigned int
    using uc8_c = unsigned c8_c;
    using uc16_c = c16_c; //Default behavior is unsigned int

    using raw_str = c8 *;
    using u_raw_str = uc8 *;
    using raw_w_str = c16 *;
    using raw_c_str = c8 const *;
    using raw_c_w_str = c16 const *;

    using i8 =  char_int<>;
    using i16 = std::int16_t;
    using i32 = std::int32_t;
    using i64 = std::int64_t;

    using ui8 = uchar_int<>;
    using ui16 = std::uint16_t;
    using ui32 = std::uint32_t;
    using ui64 = std::uint64_t;

    using i8_c = const char_int<>;
    using i16_c = const std::int16_t;
    using i32_c = const std::int32_t;
    using i64_c = const std::int64_t;

    using ui8_c = const uchar_int<>;
    using ui16_c = const std::uint16_t;
    using ui32_c = const std::uint32_t;
    using ui64_c = const std::uint64_t;

    using i8_r =  char_int<>&;
    using i16_r = std::int16_t&;
    using i32_r = std::int32_t&;
    using i64_r = std::int64_t&;

    using ui8_r = uchar_int<>&;
    using ui16_r = std::uint16_t&;
    using ui32_r = std::uint32_t&;
    using ui64_r = std::uint64_t&;

    using i8_r_c = const char_int<>&;
    using i16_r_c = const std::int16_t&;
    using i32_r_c = const std::int32_t&;
    using i64_r_c = const std::int64_t&;

    using ui8_r_c = const uchar_int<>&;
    using ui16_r_c = const std::uint16_t&;
    using ui32_r_c = const std::uint32_t&;
    using ui64_r_c = const std::uint64_t&;

    using i8_ptr = char_int<> *;
    using i16_ptr = std::int16_t *;
    using i32_ptr = std::int32_t *;
    using i64_ptr = std::int64_t *;

    using ui8_ptr = uchar_int<> *;
    using ui16_ptr = std::uint16_t *;
    using ui32_ptr = std::uint32_t *;
    using ui64_ptr = std::uint64_t *;

    using i8_ptr_c = const char_int<> *;
    using i16_ptr_c = const std::int16_t *;
    using i32_ptr_c = const std::int32_t *;
    using i64_ptr_c = const std::int64_t *;

    using ui8_ptr_c = const uchar_int<> *;
    using ui16_ptr_c = const std::uint16_t *;
    using ui32_ptr_c = const std::uint32_t *;
    using ui64_ptr_c = const std::uint64_t *;

    using i8_ptr_r = char_int<> *&;
    using i16_ptr_r = std::int16_t *&;
    using i32_ptr_r = std::int32_t *&;
    using i64_ptr_r = std::int64_t *&;

    using ui8_ptr_r = uchar_int<> *&;
    using ui16_ptr_r = std::uint16_t *&;
    using ui32_ptr_r = std::uint32_t *&;
    using ui64_ptr_r = std::uint64_t *&;

    using i8_ptr_r_c = const char_int<> *&;
    using i16_ptr_r_c = const std::int16_t *&;
    using i32_ptr_r_c = const std::int32_t *&;
    using i64_ptr_r_c = const std::int64_t *&;

    using ui8_ptr_r_c = const uchar_int<> *&;
    using ui16_ptr_r_c = const std::uint16_t *&;
    using ui32_ptr_r_c = const std::uint32_t *&;
    using ui64_ptr_r_c = const std::uint64_t *&;

    using f32 = float;
    using f64 = double;
    using f128 = typename _Select_Quad_Type<void>::type;

    using f32_c = const float;
    using f64_c = const double;
    using f128_c = const typename _Select_Quad_Type<void>::type;

    using f32_r = float&;
    using f64_r = double&;
    using f128_r = typename _Select_Quad_Type<void>::type&;

    using f32_r_c = const float&;
    using f64_r_c = const double&;
    using f128_r_c = const typename _Select_Quad_Type<void>::type&;

    using f32_ptr = float *;
    using f64_ptr = double *;
    using f128_ptr = typename _Select_Quad_Type<void>::type *;

    using f32_ptr_c = const float *;
    using f64_ptr_c = const double *;
    using f128_ptr_c = const typename _Select_Quad_Type<void>::type *;

    using f32_ptr_r = float *&;
    using f64_ptr_r = double *&;
    using f128_ptr_r = typename _Select_Quad_Type<void>::type *&;

    using f32_ptr_r_c = const float *&;
    using f64_ptr_r_c = const double *&;
    using f128_ptr_r_c = const typename _Select_Quad_Type<void>::type *&;

    using void_ptr = void *;
    using void_c_ptr = void const *;

    using size_t = std::size_t;
    using pos = size_t;
    using index = ui32;
    using indicies = std::vector<index>;
    using pid = pid_t;
    using gpid = pid_t;
    using fg_pid = pid_t;

    constexpr index const noi = 0xFFFFFFFF;

    using word = std::string;
    using word_ref = const std::string&; 
    using const_word = std::string_view&;

    using string = std::string;
    using const_string = const std::string;
    using string_ref = const std::string&;
    using string_view = std::string_view;

    using word_list = std::vector<word>;
    using word_ref_list = std::vector<const_word>&;
    using const_word_list = const std::vector<const_word>&;

    using string_list = std::vector<string>;
    using string_ref_list = std::vector<string_ref>&;
    using const_string_list = const std::vector<string_ref>&;

    using name_t = char const *;
    using name_ref = char const &;
    using names = string_list;
    using names_ref = names const &;
    using brace_t = char const *;

    using version_format_t = ui32;
    using version_brace_t = brace_t;
    using format_map = std::map<int, char const *>;

    constexpr version_format_t VER_BRACED_FORMAT = SHELL_VERSION_FORMAT_BRACED;
    constexpr version_format_t VER_SQUARE_FORMAT = SHELL_VERSION_FORMAT_SQUARE;
    constexpr version_format_t VER_PAREN_FORMAT = SHELL_VERSION_FORMAT_PARENTHESES;
    constexpr version_format_t VER_SPACED_FORMAT = SHELL_VERSION_FORMAT_SPACED;
    constexpr version_format_t VER_UNDERSCORE_FORMAT = SHELL_VERSION_FORMAT_UNDER;
    constexpr version_format_t VER_SEMANTIC_FORMAT = SHELL_VERSION_FORMAT_SEMANTIC;
    constexpr version_format_t VER_DEFAULT_FORMAT = VER_SEMANTIC_FORMAT;

    constexpr version_brace_t VER_BRACE_OPEN = SHELL_BRACE_CHAR_OPEN;
    constexpr version_brace_t VER_BRACE_CLOSE = SHELL_BRACE_CHAR_CLOSE;
    constexpr version_brace_t VER_PAREN_OPEN = SHELL_PAREN_CHAR_OPEN;
    constexpr version_brace_t VER_PAREN_CLOSE = SHELL_PAREN_CHAR_CLOSE;
    constexpr version_brace_t VER_SQUARE_OPEN = SHELL_SQUARE_CHAR_OPEN;
    constexpr version_brace_t VER_SQUARE_CLOSE = SHELL_SQUARE_CHAR_CLOSE;
    constexpr version_brace_t VER_SPACE = SHELL_CHAR_SPACE;

    constexpr name_t _shell_ = "dsh";

    const format_map version_format_delimiter_map = {

        {VER_BRACED_FORMAT, ","},
        {VER_SQUARE_FORMAT, ","},
        {VER_PAREN_FORMAT, ","},
        {VER_SPACED_FORMAT, " "},
        {VER_UNDERSCORE_FORMAT, "_"},
        {VER_SEMANTIC_FORMAT, "."},
        {VER_DEFAULT_FORMAT, "."}

    };

    inline name_t str(string_ref s) { return s.c_str(); }

    inline i8   to_i8(auto n)   { return static_cast<i8>(n); }
    inline i16  to_i16(auto n)  { return static_cast<i16>(n); }
    inline i32  to_i32(auto n)  { return static_cast<i32>(n); }
    inline i64  to_i64(auto n)  { return static_cast<i64>(n); }

    inline ui8  to_ui8(auto n)  { return static_cast<ui8>(n); }
    inline ui16 to_ui16(auto n) { return static_cast<ui16>(n); }
    inline ui32 to_ui32(auto n) { return static_cast<ui32>(n); }
    inline ui64 to_ui64(auto n) { return static_cast<ui64>(n); }

    inline f32  to_f32(auto n)  { return static_cast<f32>(n); }
    inline f64  to_f64(auto n)  { return static_cast<f64>(n); }

    inline size_t   to_size_t(auto n)   { return static_cast<size_t>(n); }
    inline pos      to_pos(auto n)      { return static_cast<pos>(n); }
    inline word     to_word(auto n)     { return static_cast<word>(n); } 

    inline char const * to_char(auto n) {return (char const*)n;}

    //flag operators
    #define FLAG_OPS(T) \
        inline T operator~(T n) { \
            return static_cast<T>(~static_cast<std::underlying_type_t<T>(n)); \
        } \
        inline T operator|(T n, T m) { \
            return static_cast<T>(static_cast<std::underlying_type_t<T>>(n) | static_cast<std::underlying_type_t<T>>(m)); \
        } \
        inline T operator&(T n, T m) { \
            return static_cast<T>(static_cast<std::underlying_type_t<T>>(n) & static_cast<std::underlying_type_t<T>>(m)); \
        } \
        inline T operator^(T n, T m) { \
            return static_cast<T>(static_cast<std::underlying_type_t<T>>(n) ^ static_cast<std::underlying_type_t<T>>(m)); \
        } \
        inline T operator|=(T n, T m) { \
            return reinterpret_cast<T&>(reinterpret_cast<std::underlying_type_t&<T>>(n) |= reinterpret_cast<std::underlying_type_t&<T>>(m)); \
        } \
        inline T operator&=(T n, T m) { \
            return reinterpret_cast<T&>(reinterpret_cast<std::underlying_type_t&<T>>(n) &= reinterpret_cast<std::underlying_type_t&<T>>(m)); \
        } \
        inline T operator^=(T n, T m) { \
            return reinterpret_cast<T&>(reinterpret_cast<std::underlying_type_t&<T>>(n) ^= reinterpret_cast<std::underlying_type_t&<T>>(m)); \
        } \

} //namespace dsh