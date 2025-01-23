#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

#include <input.hpp>

struct termios orig_termios;

void input::reset_terminal_mode()
{
    tcsetattr(0, TCSANOW, &orig_termios);
}

void input::set_conio_terminal_mode()
{
    struct termios new_termios;

    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));

    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

int input::kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}

input::Key input::getch() {
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0) {
        return input::Key::UNKNOWN;
    } else {
        switch (c) {
            case 'j':
                return input::Key::DOWN;
            case 'k':
                return input::Key::UP;
            case 'q':
                return input::Key::EXIT;
            case ' ':
                return input::Key::SPACE;
            // ctrl-c
            case 3:
                return input::Key::EXIT;
            default:
                return input::Key::UNKNOWN;
        }
    }
}
