#pragma once
#include "environment.hpp"
#include "terminal.hpp"
#include "user.hpp"

#include <iostream>

namespace dsh {

void init_shell() {

    using std::cout;

    cout << "Initializing shell for " << User().get_user_name() << "...\n";

    cout << "Home: " << Environment::get_home() << '\n';
    cout << "Shell: " << Environment::get_shell() << '\n';
    cout << "Path: " << Environment::get_path() << '\n';

    Terminal::enable_raw();
    atexit(Terminal::disable_raw);

}

}