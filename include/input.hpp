#ifndef INPUT_HPP_
#define INPUT_HPP_

namespace input {
    enum class Key {
        UP,
        DOWN,
        SPACE,
        EXIT,
        UNKNOWN
    };

    void reset_terminal_mode();

    void set_conio_terminal_mode();

    int kbhit();

    Key getch();
}


#endif
