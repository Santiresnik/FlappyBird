#include "physics.h"
#include <stdlib.h>

static void update_pipes(GameState* state, float dt);

void physics_update(GameState* state, float dt){
    state->bird.velocity += state->config.gravity * dt;
    state->bird.y += state->bird.velocity * dt;
    if(state->bird.y > WORLD_HEIGHT){
        state->bird.y = WORLD_HEIGHT;
        state->bird.velocity = 0;
    }
    update_pipes(state, dt);
}

static void update_pipes(GameState* state, float dt){
    state->pipe_spawn_timer += dt;
    for(int i=0; i<MAX_PIPES; i++){
        Pipe* pipe = &state->pipes[i];
        if(pipe->active){
            pipe->x += state->config.pipe_speed * dt;
            if(pipe->x + state->config.pipe_width < 0){
                pipe->active = 0;
            }
        }
    }

    if(state->pipe_spawn_timer >= state->config.pipe_spawn_interval){
        int done = 0;
        for(int i=0; i<MAX_PIPES && !done; i++){
            Pipe* pipe = &state->pipes[i];
            if(!pipe->active){
                pipe->x = WORLD_WIDTH;
                pipe->gap_y = PIPE_GAP_MIN + ((float)rand()/(float)RAND_MAX)*(PIPE_GAP_MAX - PIPE_GAP_MIN);
                pipe->active = 1;
                done = 1;
            }
        }
        state->pipe_spawn_timer = 0.0f;
    }
}

int physics_check_collision(const GameState* state){
    int collision = 0;
    if(state->bird.y < 0){
        collision = 1;
    }
    else{
        for(int i=0; i<MAX_PIPES; i++){
            Pipe pipe = state->pipes[i];
            float bx = state->bird.x;
            float by = state->bird.y;
            if(pipe.active &&
              (bx > pipe.x && bx > (pipe.x + state->config.pipe_width)) &&
              (by < pipe.gap_y || by >(pipe.gap_y + state->config.pipe_gap_height))){
                collision = 1;
            }
        }
    }
    return collision;
}