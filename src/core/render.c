#include "render.h"
#include "curses_wrapper.h"

void render_init(void) {
    savetty();
    initscr();            // Start curses mode
    cbreak();             // Disable line buffering
    noecho();             // Don’t echo pressed keys
    keypad(stdscr, TRUE); // Enable special keys (arrows, etc.)
    curs_set(0);          // Hide cursor
    nodelay(stdscr, TRUE); // Non-blocking input
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_YELLOW, COLOR_BLACK); // bird
        init_pair(2, COLOR_GREEN, COLOR_BLACK);  // pipes
        init_pair(3, COLOR_WHITE, COLOR_BLACK);  // score
    }
    clear();
}

void render_shutdown(void) {
    if (has_colors()) {
        attroff(COLOR_PAIR(1));
        attroff(COLOR_PAIR(2));
        attroff(COLOR_PAIR(3));
    }
    curs_set(1); // Show cursor again
    endwin();    // End curses mode
    resetty();   // Restore saved terminal state
}