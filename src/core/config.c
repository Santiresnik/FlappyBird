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

int read_high_scores(HighScore *scores, int max_scores) {
    
    HighScore all_scores[MAX_TOTAL_SCORES];
    FILE *f = fopen("scores.txt", "r");
    if (!f) return 0;
    int total_count = 0;
    while (total_count < MAX_TOTAL_SCORES && fscanf(f, "%3s %d", all_scores[total_count].name, &all_scores[total_count].score) == 2) {
        total_count++;
    }
    fclose(f);

    // Sort all scores from highest to lowest
    for (int i = 0; i < total_count - 1; i++) {
        for (int j = i + 1; j < total_count; j++) {
            if (all_scores[j].score > all_scores[i].score) {
                HighScore temp = all_scores[i];
                all_scores[i] = all_scores[j];
                all_scores[j] = temp;
            }
        }
    }

    // Copy only the top max_scores to the output array
    int count = (total_count < max_scores) ? total_count : max_scores;
    for (int i = 0; i < count; i++) {
        scores[i] = all_scores[i];
    }

    return count;
}