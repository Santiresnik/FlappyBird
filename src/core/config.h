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
#define TICKRATE 30
#define TIMESTEP 1.0f/TICKRATE
#define WORLD_HEIGHT 30.0f // Game units, by default matches the height and width of the terminal grid
#define WORLD_WIDTH 120.0f
#define FLOOR_HEIGHT (WORLD_HEIGHT/10.0f) // Height of the floor in game units, used to determine collision with the ground

#define RAND_MARGIN_PERCENT 10.0f
#define PIPE_GAP_MIN (WORLD_HEIGHT*(0.5f - RAND_MARGIN_PERCENT/100.0f) - DEFAULT_PIPE_GAP_HEIGHT)
#define PIPE_GAP_MAX (WORLD_HEIGHT*(0.5f + RAND_MARGIN_PERCENT/100.0f))

#define MAX_USERNAME_LEN 3 //3 chars + null terminator
#define MAX_SCORES 3 //only 3 highest scores are stored
#define MAX_TOTAL_SCORES 1000 // capacity of scores.txt


#define DEFAULT_START_POS_X (WORLD_WIDTH/4.0f)
#define DEFAULT_START_POS_Y (WORLD_HEIGHT/2.0f)
#define DEFAULT_GRAVITY (-1.0f*WORLD_HEIGHT) // (game units / s^2) Reaches bottom in 1 second starting from the middle with no initial velocity
#define DEFAULT_JUMP_STRENGTH (-0.4f*DEFAULT_GRAVITY) // (game units / s)
#define DEFAULT_PIPE_SPEED (-WORLD_WIDTH/4.0f) // (game units / s) Moves across the screen in 4 seconds
#define DEFAULT_PIPE_GAP_HEIGHT (WORLD_HEIGHT/6.0f) // (game units) Gap height between pipes
#define DEFAULT_PIPE_WIDTH (WORLD_WIDTH/30.0f)
#define DEFAULT_PIPE_SPAWN_INTERVAL 2.0f // (seconds) Time between pipe spawns
#define DEFAULT_JUMP_KEY ' ' // Space key by default
#define DEFAULT_LIVES 3
#define DEFAULT_COLLISION_TIMER 2.0f // 3 seconds grace period after collision

typedef struct {
    float gravity;
    float jump_strength;
    float pipe_speed;
    float pipe_spawn_interval;
    float pipe_gap_height;
    float pipe_width;
    char jump_key;
} GameConfig;

typedef struct {
    char name[4];
    int score;
} HighScore;

void loadDefaultConfig(GameConfig* config);
void historyLog(const char* username, int score);
int read_high_scores(HighScore *scores, int max_scores);
#endif
