/*
This header defines core constants used throughout the game, such as
world dimensions, timing parameters, and pipe behavior constraints.
It also defines the GameConfig structure, which encapsulates configurable
parameters affecting gameplay and allows them to be loaded or modified.

GameConfig:

Holds the runtime configuration used by the game engine. Should be initialized using loadDefaultConfig().

*/
#ifndef CONFIG_H
#define CONFIG_H

#define MAX_PIPES 8
#define MAX_USERNAME_LEN 20
#define TICKRATE 30
#define TIMESTEP 1.0f/TICKRATE
#define WORLD_HEIGHT 100
#define WORLD_WIDTH 100
#define RAND_MARGIN_PERCENT 10
#define PIPE_GAP_MIN (WORLD_HEIGHT*(0.5f - RAND_MARGIN_PERCENT/100.0f))
#define PIPE_GAP_MAX (WORLD_HEIGHT*(0.5f + RAND_MARGIN_PERCENT/100.0f))
//TODO: Set useful default values
#define DEFAULT_START_POS_X 0
#define DEFAULT_START_POS_Y 0
#define DEFAULT_GRAVITY 0
#define DEFAULT_JUMP_STRENGTH 0
#define DEFAULT_PIPE_SPEED 0
#define DEFAULT_PIPE_GAP_HEIGHT 0
#define DEFAULT_PIPE_WIDTH 0
#define DEFAULT_PIPE_SPAWN_INTERVAL 0
#define DEFAULT_JUMP_KEY 0
#define DEFAULT_LIVES 3

typedef struct {
    float gravity;
    float jump_strength;
    float pipe_speed;
    float pipe_spawn_interval;
    int pipe_gap_height;
    int pipe_width;
    char jump_key;
} GameConfig;

void loadDefaultConfig(GameConfig* config);
#endif
