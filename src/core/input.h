#ifndef INPUT_H
#define INPUT_H

typedef enum {
    INPUT_NONE,
    INPUT_SPACE,
    INPUT_ESC,
    INPUT_ENTER,
    INPUT_UP,
    INPUT_DOWN,
    INPUT_LEFT,
    INPUT_RIGHT,
    INPUT_OTHER
} InputAction;

InputAction input_poll(void);
#endif