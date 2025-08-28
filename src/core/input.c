/*
 Implements the input polling logic using ncurses or PDCurses depending on whether 
 the game is being compiled for Windows or Linux.
 
 Uses (n)curses.h function getch() to check if a key has been pressed (non blocking
 if configured properly) including special keys like arrow keys.

 The function input_poll_windows() returns an InputAction enum value representing
 the detected key press or INPUT_NONE if no key is pressed.

 Usage:

 - Ensure that either the WINDOWS or LINUX macro is defined at compile time.
 - Do not define both at once, or the compilation will fail.
 - Calls input_poll_windows or input_poll_linux accordingly.
 - Includes error checks to prevent conflicting or missing platform definitions.

 */

#include "input.h"
#include "curses_wrapper.h"
InputAction input_poll(void){
    InputAction input;
    int ch = getch();
    if(ch == ERR){
        input = INPUT_NONE;
    }
    else{   
        switch (ch) {
            case KEY_UP: 
                input = INPUT_UP;
                break;
            case KEY_DOWN: 
                input = INPUT_DOWN;
                break;
            case KEY_LEFT: 
                input = INPUT_LEFT;
                break;
            case KEY_RIGHT: 
                input = INPUT_RIGHT;
                break;
            case 27: 
                input = INPUT_ESC;
                break;
            case ' ': 
                input = INPUT_SPACE;
                break;
            case '\n':
            case '\r':
                input = INPUT_ENTER;
                break; 
            default: 
                input = INPUT_OTHER;
                break;
        }
    }
    return input;
}

void input_nickname(NicknameState* state, InputAction input) {
    switch (input) {
        case INPUT_LEFT:
            if (state->pos > 0) state->pos--;
            break;
        case INPUT_RIGHT:
            if (state->pos < MAX_USERNAME_LEN-1) state->pos++;
            break;
        case INPUT_UP:
            if (state->letters[state->pos] < 'Z') state->letters[state->pos]++;
            break;
        case INPUT_DOWN:
            if (state->letters[state->pos] > 'A') state->letters[state->pos]--;
            break;
        case INPUT_ENTER:
            state->done = 1;
            break;
        default:
            break;
    }
}
