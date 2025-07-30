#ifndef GAME_H
#define GAME_H
#include "config.h"
#include "input.h"
typedef struct {
    float x;
    float y;
    float velocity;
} Bird;

typedef struct {
    float x;
    float gap_y;
    int active;
} Pipe;

typedef enum {
    STATE_MENU,
    STATE_PLAYING,
    STATE_GAME_OVER,
    STATE_QUIT
} GameStateId;

typedef struct {
    GameStateId current;
    Bird bird;
    Pipe pipes[MAX_PIPES];
    float pipe_spawn_timer;
    int score;
    int lives;
    int is_game_over;
    GameConfig config;
    char username[MAX_USERNAME_LEN];
} GameState;

void game_init(GameState *game);
void game_update(GameState *game, float delta_time, InputAction jump_input);
int game_check_collision(GameState *game);
void game_reset(GameState *game);

#endif