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
    int nickname_entered = 0;
    NicknameState nickname_state = { .letters={'A','A','A'}, .pos=0, .done=0 };
    
    while (running) {
        current_time = get_current_time();
        dt = current_time - previous_time;
        previous_time = current_time;
        key = input_poll(); //Input key   

        switch (game.current) {
            case STATE_MENU:
                if (!nickname_entered) {
                    render_nickname(&nickname_state);
                    input_nickname(&nickname_state, key);
                    
                    if (nickname_state.done) {
                        for (int i = 0; i < 3; i++){
                            game.username[i] = nickname_state.letters[i];
                        }
                        game.username[MAX_USERNAME_LEN] = '\0';
                        nickname_entered = 1;
                    }                
                }
                else {
                    render_menu(&game);
                    if (key == INPUT_SPACE || key == INPUT_ENTER) {
                        game_reset(&game);
                        game.current = STATE_PLAYING;
                        nickname_entered = 0; // Reset for next time you return to menu
                    } else if (key == INPUT_ESC) {
                        game.current = STATE_QUIT;
                    }
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
                //add_high_score(game.username, game.score);
                render_gameover(&game);
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