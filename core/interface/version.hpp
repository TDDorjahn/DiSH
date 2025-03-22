#pragma once
#include "def.hpp"
#include "osdef.hpp"
#include "types.hpp"
#include "concepts.hpp"

#include <sstream> //for string version creation

using std::ostringstream; //used to build string of semantic version

//Base Version struct Object Concept
template <typename _Version_Type>
concept Ver_Type = std::is_object_v<_Version_Type>;

//Reference Version struct Object Concept
template <typename _Version_Ref_Type>
concept Ver_Ref_Type = std::is_reference_v<_Version_Ref_Type>;

//Pointer (or Reference) Version struct Object Concept
template <typename _Version_Ptr_Type>
concept Ver_Ptr_Type = Ver_Ref_Type<_Version_Ptr_Type> || std::is_pointer_v<_Version_Ptr_Type>;

//Compound Ptr/Ref/Obj Version struct Object Concept
template <typename _Version_Any_Type>
concept Ver_Any_Type = Ver_Ptr_Type<_Version_Any_Type> || Ver_Type<_Version_Any_Type>;

namespace dsh {

enum class stage : index {

    preview,
    alpha,
    beta,
    release,
    dev

};

struct version {

    ui32 major = SHELL_VERSION_MAJOR;
    ui32 minor = SHELL_VERSION_MINOR;
    ui32 patch = SHELL_VERSION_PATCH;

    ui32 year = 2025;
    ui32 release = 0;
    stage st = stage::dev;
    ui32 rev = 0;

    auto operator<=>(version const&) const = default;

};

inline version get_version(string_ref str) {

    version result{0,0,0};

#ifdef DSH_WIN
    sscanf_s
#else
    sscanf
#endif
    (str.c_str(), "%d.%d.%d", &result.major, &result.minor, &result.patch);
    return result;

}

template<Ver_Any_Type Version>
inline string_ref get_version_str(Version const &obj, version_format_t const FORMAT = VER_DEFAULT_FORMAT) {

    char const * delim = version_format_delimiter_map.at(FORMAT);
    char const * sect_open = "", * sect_close = "";

    if(FORMAT == VER_BRACED_FORMAT) {
         sect_open = VER_BRACE_OPEN; sect_close = VER_BRACE_CLOSE;
    }
    else if(FORMAT == VER_PAREN_FORMAT) {
        sect_open = VER_PAREN_OPEN; sect_close = VER_PAREN_CLOSE;
    }
    else if(FORMAT == VER_SQUARE_FORMAT){
        sect_open = VER_SQUARE_OPEN; sect_close = VER_SQUARE_CLOSE;
    }
    else {
        sect_open = ""; sect_close = "";
    }

    ostringstream oss;

    if constexpr (Pointer<Version>) {

        oss << sect_open << obj->major << delim << obj->minor << delim << obj->patch << sect_close;

    } else { 

        oss << sect_open << obj.major << delim << obj.minor << delim << obj.patch << sect_close;

    }

    string_ref str = oss.str();

    return str;


}

constexpr name_t dbg_build_date = SHELL_BUILD_DATE;
constexpr name_t dbg_build_time = SHELL_BUILD_TIME;

}