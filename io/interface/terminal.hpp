#pragma once
#include <termios.h>

namespace dsh {

class Terminal {

public:

    static void enable_raw();
    static void disable_raw();

private:

    static struct termios original_terminal;

};

struct termios Terminal::original_terminal;

}