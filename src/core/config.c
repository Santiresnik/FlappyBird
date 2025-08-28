/*
This file contains the implementation of the loadDefaultConfig function,
which initializes a GameConfig struct with predefined default constants.
These settings control core gameplay elements such as gravity, jump strength,
pipe behavior, and input controls.

Usage:

- Call loadDefaultConfig(&config) at game initialization to ensure the
game starts with consistent parameters.

*/
#include "config.h"
#include <stdio.h>

void loadDefaultConfig(GameConfig* config) {
    config->gravity = DEFAULT_GRAVITY;
    config->jump_strength = DEFAULT_JUMP_STRENGTH;
    config->pipe_speed = DEFAULT_PIPE_SPEED;
    config->pipe_gap_height = DEFAULT_PIPE_GAP_HEIGHT;
    config->pipe_width = DEFAULT_PIPE_WIDTH;
    config->pipe_spawn_interval = DEFAULT_PIPE_SPAWN_INTERVAL;
    config->jump_key = DEFAULT_JUMP_KEY;
}

void historyLog(const char* username, int score){
    FILE *file = fopen("scores.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %d\n", username, score);
        fclose(file);
    }
}