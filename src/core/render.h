#ifndef RENDER_H
#define RENDER_H

#include "game.h"

void render_init(void);
void render_shutdown(void);
void render_draw(const GameState*);

#endif