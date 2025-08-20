#include "render.h"
#include "curses_wrapper.h"

#define BIRD_SYMBOL '>'
#define PIPE_SYMBOL ' '
#define MAP(ix, il, ih, ol, oh) ((ol) + (((ix)-(il))*((oh)-(ol)))/((ih)-(il)))
#define ROUND(x) (((x) - (int)(x)) >= 0.5f ? (int)(x) + 1 : (int)(x))

static void game_to_screen_xy(int rows, int cols, float gx, float gy, int* psx, int* psy);

static int rows;
static int cols;

void render_init(void) {
    savetty();
    initscr();            // Start curses mode
    noecho();             // Don’t echo pressed keys
    keypad(stdscr, TRUE); // Enable special keys (arrows, etc.)
    curs_set(0);          // Hide cursor
    cbreak();             // Disable line buffering
    nodelay(stdscr, TRUE); // Non-blocking input
    getmaxyx(stdscr, rows, cols);
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_YELLOW, COLOR_BLACK); // bird
        init_pair(2, COLOR_GREEN, COLOR_GREEN);  // pipes
        init_pair(3, COLOR_WHITE, COLOR_BLACK);  // score
    }
    clear();
}

void render_shutdown(void) {
    if (has_colors()) {
        attroff(COLOR_PAIR(1));
        attroff(COLOR_PAIR(2));
        attroff(COLOR_PAIR(3));
    }
    curs_set(1); // Show cursor again
    endwin();    // End curses mode
    resetty();   // Restore saved terminal state
}

void render_draw(const GameState* game){
    int bx, by, pipe_x, pipe_gap_y;
    int pipe_width = ROUND(((float)cols/WORLD_WIDTH)*(game->config.pipe_width));
    int pipe_gap_height = ROUND(((float)rows/WORLD_HEIGHT)*(game->config.pipe_gap_height));
    game_to_screen_xy(cols, rows, game->bird.x, game->bird.y, &bx, &by);

    erase();
    
    attron(COLOR_PAIR(1));
    if (game->collision_timer > 0) {
        // Blink: only show the bird if "timer * 10" is even
        if (((int)(game->collision_timer * 10)) % 2 == 0) {
            mvaddch(by, bx, BIRD_SYMBOL);
        }
    } else {
        // Normal render
        mvaddch(by, bx, BIRD_SYMBOL);
    }
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    for(int i = 0; i<MAX_PIPES; i++){
        Pipe pipe = game->pipes[i];
        if(pipe.active){
            game_to_screen_xy(cols, rows, pipe.x, pipe.gap_y, &pipe_x, &pipe_gap_y);
            for(int j = 0; j<rows; j++){
                if(j<(pipe_gap_y-pipe_gap_height) || j>=pipe_gap_y){
                    mvhline(j, pipe_x, PIPE_SYMBOL, pipe_width);
                }
            }
        }
    }
    attroff(COLOR_PAIR(2));

    // Draw score
    attron(COLOR_PAIR(3));
    mvprintw(0, cols - 12, "Score: %d", game->score);
    attroff(COLOR_PAIR(3));

    //Draw lives
     attron(COLOR_PAIR(3));
    mvprintw(0, 0, "Lives: ");  // Position top-left corner
    for (int i = 0; i < game->lives; i++) {
        mvprintw(0, 7 + i*2, HEART);  // Print hearts with spacing
    }
    attroff(COLOR_PAIR(3));

    refresh();
}

static void game_to_screen_xy(int scr_width, int scr_height, float gx, float gy, int* psx, int* psy){
    *psx = ROUND(MAP(gx, 0, WORLD_WIDTH-1, 0, scr_width-1));
    *psy = ROUND(MAP(gy, 0, WORLD_HEIGHT-1, scr_height-1, 0));
}

void render_menu(const GameState* game){

}

void render_gameover(const GameState* game){

}
