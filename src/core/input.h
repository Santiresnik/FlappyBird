#ifndef INPUT_H
#define INPUT_H
#include "config.h"
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

typedef struct {
    char letters[MAX_USERNAME_LEN];
    int pos;
    int done;
} NicknameState;

InputAction input_poll(void);
void input_nickname(NicknameState *state, InputAction input);

#endif
