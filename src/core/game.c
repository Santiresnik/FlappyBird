/*
This file defines the main logic for initializing, updating, and resetting
the game state. It interfaces with configuration settings and is responsible
for managing the lifecycle of key game elements such as the bird and pipes.

Functions:

- game_init: Sets up the initial game state and loads default configuration.
- game_update: Handles per-frame logic.
- game_reset: Resets the game state to its initial condition.
- game_handle_collision: Handles player collision and life management.
*/

#include "game.h"
#include "physics.h"

void game_init(GameState* game) {
    loadDefaultConfig(&game->config);
    game->score = 0;
    game->lives = DEFAULT_LIVES;
    game->is_game_over = 0;
    game->bird.x = DEFAULT_START_POS_X;
    game->bird.y = DEFAULT_START_POS_Y;
    game->bird.velocity = 0;
    game->collision_timer = 0.0f;

    for (int i = 0; i < MAX_PIPES; i++) {
        game->pipes[i].active = 0;
    }
}

void game_update(GameState* game, float delta_time, InputAction input) {

    if (game->is_game_over) return;

    // Handle jump input
    if (input == INPUT_SPACE) {
        game->bird.velocity = game->config.jump_strength;
    }

    // Update physics (bird, pipes, spawning)
    physics_update(game, delta_time);

    // Scoring: increment score when bird passes a pipe
    for (int i = 0; i < MAX_PIPES; i++) {
        Pipe* pipe = &game->pipes[i];
        if (pipe->active &&
            pipe->x + game->config.pipe_width < game->bird.x) {
            game->score++;
            pipe->active = 0;
        }
    }

    // Grace period
    if (game->collision_timer > 0.0f) {
        game->collision_timer -= delta_time;
        return;
    }

    // Collision check
    if (physics_check_collision(game) && game->collision_timer <= 0) {
        game_handle_collision(game);
        game->collision_timer = DEFAULT_COLLISION_TIMER;

    }
}

void game_reset(GameState* game) {
    game_init(game);
}

void game_handle_collision(GameState* game) {
    game->lives--;
    if (game->lives <= 0) {
        game->is_game_over = 1;
    } else {
        // We could reset bird position and velocity for next life
    }
}
