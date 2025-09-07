#ifndef RENDER_H
#define RENDER_H

#include "game.h"
#include "input.h"

void render_init(void);
void render_shutdown(void);
void render_draw(const GameState*);
void render_menu(const GameState* game);
void render_pause(const GameState* game);
void render_gameover(const GameState* game);
void render_nickname(const NicknameState* state);

#endif