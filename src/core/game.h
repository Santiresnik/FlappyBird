/*
This header defines the structures and enumerations used to represent
the game’s internal state, such as the player’s bird, pipes,
configuration, and overall game status. It also declares functions for
initializing, updating, resetting, and checking collisions in the game.

Structures:

- Bird: Represents the player's avatar with position and velocity.
- Pipe: Represents a pipe obstacle, with x position and gap location.
- GameState: Holds the entire current state of the game including bird,
pipes, score, configuration, and game mode.

GameStateId: Enum representing the current phase of the game (e.g., menu, playing).

*/
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
    float collision_timer; // Grace period timer

} GameState;

void game_init(GameState *game);
void game_update(GameState *game, float delta_time, InputAction jump_input);
int game_check_collision(GameState *game);
void game_reset(GameState *game);

#endif