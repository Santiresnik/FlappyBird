/*
 Implements the input polling logic for Windows console.
 Uses conio.h functions _kbhit() and _getch() to check if a key has been pressed
 and then reads the key code, including special keys like arrow keys.

 The function input_poll_windows() returns an InputAction enum value representing
 the detected key press or INPUT_NONE if no key is pressed.
 
 Arrow keys produce two-character codes: first 0 or 224, then a code for the arrow.
 The function handles this and maps keys to meaningful input actions for the game.
*/
#include "input_windows.h"
#include <conio.h>

InputAction input_poll_windows(void){
    InputAction input;
    if(!_kbhit()){
        input = INPUT_NONE;
    }
    else{
        int ch = _getch();
            
        if (ch == 0 || ch == 224) {
            int special = _getch();
            switch (special) {
                case 72: 
                    input = INPUT_UP;
                    break;
                case 80: 
                    input = INPUT_DOWN;
                    break;
                case 75: 
                    input = INPUT_LEFT;
                    break;
                case 77: 
                    input = INPUT_RIGHT;
                    break;
                default: 
                    input = INPUT_OTHER;
                    break;
            }
        } else {
            switch (ch) {
                case 27: 
                    input = INPUT_ESC;
                    break;
                case ' ': 
                    input = INPUT_SPACE;
                    break;
                case '\n':
                    input = INPUT_ENTER;
                    break; 
                default: 
                    input = INPUT_OTHER;
                    break;
            }
        }
    }
    return input;
}