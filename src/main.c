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
        float dt = get_current_time();
        int key; //Input key, needs function

        switch (current) {
            case STATE_MENU:
                if (key == ' ' || key == '\n') { //just to fill, does not mean this is how game will work
                    game_reset(&game);
                    current = STATE_PLAYING;
                } else if (key == 'q') {
                    current = STATE_QUIT;
                }
                break;

            case STATE_PLAYING:
                game_update(&game, dt, key);
                render_draw_game(&game);
                if (game.is_game_over) {
                    current = STATE_GAME_OVER;
                }
                break;

            case STATE_GAME_OVER: //just for now, maybe we change, with r reset and q quit
                render_draw_game_over(&game);
                if (key == 'r') {
                    game_reset(&game);
                    current = STATE_PLAYING;
                } else if (key == 'q') {
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
