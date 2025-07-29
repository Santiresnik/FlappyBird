#include <stdio.h>
#include "game.h"
#include "input.h"
#include "timer.h"

typedef enum {
    STATE_MENU,
    STATE_PLAYING,
    STATE_GAME_OVER,
    STATE_QUIT
} GameScreen;

int main() {
    GameState game;
    GameScreen current = STATE_MENU;

    game_init(&game);

    int running = 1;
    while (running) {
        float dt = get_delta_time();
        int key = input_poll; //Input key

        switch (current) {
            case STATE_MENU:
                    game_reset(&game);
                    current = STATE_PLAYING;
                } else if (key == INPUT_ESC) {
                    current = STATE_QUIT;
                }
                break;

            case STATE_PLAYING:
                game_update(&game, dt, key);
                if (game.is_game_over) {
                    current = STATE_GAME_OVER;
                }
                break;

            case STATE_GAME_OVER: 
                if (key == INPUT_SPACE || key == INPUT_ENTER) {
                    game_reset(&game);
                    current = STATE_PLAYING;
                } else if (key == INPUT_ESC) {
                    current = STATE_QUIT;
                }
                break;

            case STATE_QUIT:
                running = 0;
                break;
        }

    }

    return 0;
}
