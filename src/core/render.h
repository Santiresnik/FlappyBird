#ifndef RENDER_H
#define RENDER_H

#include "game.h"

void render_init(void);
void render_shutdown(void);
void render_draw(const GameState*);
void render_menu(const GameState* game);
void render_gameover(const GameState* game);
void input_get_nickname(GameState* game);


#endif