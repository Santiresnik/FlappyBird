#include "game.h"
void game_init(GameState* game) {
    loadDefaultConfig(&game->config);
    game->score = 0;
    game->lives = DEFAULT_LIVES;
    game->is_game_over = 0;
    game->bird.x = DEFAULT_START_POS_X;
    game->bird.y = DEFAULT_START_POS_Y;
    game->bird.velocity = 0;

    for (int i = 0; i < MAX_PIPES; i++) {
        game->pipes[i].active = 0;
    }
}

void game_update(GameState* game, float delta_time, InputAction input) {
    // TODO: Handle input, update physics, check collisions
}

void game_reset(GameState* game) {
    game_init(game);
}

void game_handle_collision(GameState* game) {
    // TODO: Decrease lives, check for game over
}
