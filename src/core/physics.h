#ifndef PHYSICS_H
#define PHYSICS_H

#include "game.h"
int Bird_Y_Init (void);
void physics_update(GameState* state, float dt);
int physics_check_collision(const GameState* state);
#endif
