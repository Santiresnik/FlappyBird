#ifndef CONFIG_H
#define CONFIG_H

#define MAX_PIPES 8
#define MAX_USERNAME_LEN 20
#define TICKRATE 30
#define TIMESTEP 1.0f/TICKRATE

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
