#include "config.h"

void loadDefaultConfig(GameConfig* config) {
    config->gravity = DEFAULT_GRAVITY;
    config->jump_strength = DEFAULT_JUMP_STRENGTH;
    config->pipe_speed = DEFAULT_PIPE_SPEED;
    config->pipe_gap_height = DEFAULT_PIPE_GAP_HEIGHT;
    config->pipe_width = DEFAULT_PIPE_WIDTH;
    config->pipe_spawn_interval = DEFAULT_PIPE_SPAWN_INTERVAL;
    config->jump_key = DEFAULT_JUMP_KEY;
}
