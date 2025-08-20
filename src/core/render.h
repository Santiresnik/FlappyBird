#ifndef RENDER_H
#define RENDER_H

#include "game.h"
#define HEART "<3"

void render_init(void);
void render_shutdown(void);
void render_draw(const GameState*);
void render_menu(const GameState* game);
void render_gameover(const GameState* game);


#endif