#pragma once
#include "types.hpp"

namespace dsh {

class User {

public:

    User();
    string_ref get_user_name();
    string_ref get_home_dir();

private:
    string user_name;
    string home_dir;

};

}