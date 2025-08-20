/**
This file contains the main game loop and handles the high-level game state transitions
such as switching between the menu, playing, game over, and quit states.
It initializes the game, seeds the random number generator, calculates frame delta time,
processes input, and updates the game logic accordingly.

Key components used:
- GameState: Holds the current game data and status.
- InputAction: Represents user input actions.
- Timer: Used to calculate frame timing for smooth updates.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "core/game.h"
#include "core/input.h"
#include "core/timer.h"
#include "core/render.h"

int main() {
    srand(time(NULL));
    float previous_time = get_current_time();
    float current_time, dt;
    InputAction key;
    GameState game;
    game_init(&game);
    render_init();
    int running = 1;
    while (running) {
        current_time = get_current_time();
        dt = current_time - previous_time;
        previous_time = current_time;
        key = input_poll(); //Input key
        switch (game.current) {
            case STATE_MENU:
                if (key == INPUT_SPACE || key == INPUT_ENTER) { //just to fill, does not mean this is how game will work
                    game_reset(&game);
                    game.current = STATE_PLAYING;
                } else if (key == INPUT_ESC) {
                    game.current = STATE_QUIT;
                }
                break;
            case STATE_PLAYING:
                game_update(&game, dt, key);
                render_draw(&game);
                if (game.is_game_over) {
                    game.current = STATE_GAME_OVER;
                }
                break;
            case STATE_GAME_OVER: //just for now, maybe we change, with r reset and q quit
                //render_draw_game_over(&game);
                if (key == INPUT_SPACE || key == INPUT_ENTER) {
                    game_reset(&game);
                    game.current = STATE_PLAYING;
                } else if (key == INPUT_ESC) {
                    game.current = STATE_QUIT;
                }
                break;
            case STATE_QUIT:
                running = 0;
                break;
        }
    }
    render_shutdown();
    return 0;
}
