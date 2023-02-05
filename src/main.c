/*
NOTES FOR FUTURE ME OR READER (labeled with letters at the beginning):
1. X is horizontal, Y is vertical. (0X, 0Y) = top left
2. I did this in one night, and haven't touched C in a year. Please excuse my
   sh*tty code.
3. Meta-note: the notes are ordered not by line, but chronologically according
   to when I wrote them. This is NOT because I am lazy (read: I'm super lazy).
*/

#include "types.h"

#include "sdl_interface.h"

int main() {
    struct SDLState *guts = init();

    bool running = true;

    while (running) {
        switch (process_events(guts)) {
            case EC_QUIT:
                running = false;
                break;
            default:
                break;
        }
    }

    deinit(guts);
}
