#include "user.hpp"

namespace dsh {

    User::User() { 

        user_name = getenv("USER") ? getenv("USER") : "unknown";
        home_dir = getenv("HOME") ? getenv("HOME") : "/";

    }

    string_ref User::get_user_name() { return user_name; }
    string_ref User::get_home_dir() { return home_dir; }

}