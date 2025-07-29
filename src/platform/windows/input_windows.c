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