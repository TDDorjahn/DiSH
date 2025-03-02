#pragma once
#include "types.hpp"
#include <cstdlib>

namespace dsh {

class Environment {

public:

    static string get_home() { return getenv("HOME") ? getenv("HOME") : "/"; }
    static string get_path() { return getenv("PATH") ? getenv("PATH") : "/"; }
    static string get_shell() { return getenv("SHELL") ? getenv("SHELL") : "/"; }

private:

    static string home;
    static string path;
    static string shell;

};

}