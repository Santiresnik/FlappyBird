/**
 ******************************************************************************
 * @file    : main.c
 * @date    : May 8, 2025
 * @authors : Juan Ignacio Fogolin Lagares, Santiago Resnik, Hyunjong Lee, Felix Bahrke
 * @brief   : Game logic and core loop for Flappy Bird (console version)
 ******************************************************************************
 * @attention
 * 
 * Copyright (c) 2025.
 * All rights reserved.
 * Non-commercial use only. No liability is assumed by the authors.
 * 
 ******************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <output.h>  // Assumed to contain drawScreen(), keyinpt(), savegame(), startscreen()

// ─────────────────────────────────────────────────────────────────────────────
// Global Variables
// ─────────────────────────────────────────────────────────────────────────────

Bird bird;
Pipe pipes[pipeCount];
Score score;
int running = 1;  // 1 = true, 0 = false

// ─────────────────────────────────────────────────────────────────────────────
// Game Initialization
// ─────────────────────────────────────────────────────────────────────────────

void initGame() {
    bird.y = SCREEN_HEIGHT / 2;
    bird.velocity = 1.0;

    for (int i = 0; i < pipeCount; i++) {
        pipes[i].x = SCREEN_WIDTH + i * (SCREEN_WIDTH / pipeCount);
        pipes[i].gap_y = rand() % (SCREEN_HEIGHT - GAP_HEIGHT - 2) + 1;
    }

    score.lifes = 3;
    score.tubepassed = 0;
}

// ─────────────────────────────────────────────────────────────────────────────
// Collision Detection and Pipe Updates
// ─────────────────────────────────────────────────────────────────────────────

void checkCollisionsAndUpdatePipes(Bird *bird, Pipe pipes[], int count, int *running) {
    for (int i = 0; i < count; i++) {
        pipes[i].x--;

        int atPipe = (flappy_xpos == pipes[i].x);
        int hitPipe = (bird->y < pipes[i].gap_y) || (bird->y > pipes[i].gap_y + GAP_HEIGHT);

        if (atPipe) {
            if (hitPipe) {
                score.lifes--;
                if (score.lifes < 0) {
                    savegame(&score);
                    printf("\nGame Over! Restarting...\n");
                    Sleep(5000);
                    startscreen(&score);
                    initGame();
                    return;
                }
            } else {
                score.tubepassed++;
            }
        }

        if (pipes[i].x + PIPE_WIDTH < 0) {
            pipes[i].x = SCREEN_WIDTH - 1;
            pipes[i].gap_y = rand() % (SCREEN_HEIGHT - GAP_HEIGHT - 2) + 1;
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Bird Movement and Input
// ─────────────────────────────────────────────────────────────────────────────

void updateMovement(Bird *bird) {
    bird->velocity += 0.2;
    bird->y += bird->velocity;

    char input = keyinpt();
    if (input == ' ') {
        bird->velocity = -1.5;
    }

    if (bird->y >= SCREEN_HEIGHT - 1) {
        bird->y = SCREEN_HEIGHT - 1;
    } else if (bird->y < 0) {
        bird->y = 0;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Main Function
// ─────────────────────────────────────────────────────────────────────────────

int main() {
    startscreen(&score);
    srand(time(NULL));
    initGame();

    while (running) {
        updateMovement(&bird);
        checkCollisionsAndUpdatePipes(&bird, pipes, pipeCount, &running);
        drawScreen(&bird, pipes, pipeCount);
        Sleep(50);
    }

    return 0;
}
