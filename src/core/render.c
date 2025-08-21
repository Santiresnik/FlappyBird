#include "render.h"
#include "curses_wrapper.h"

#define DEFAULT_BIRDSYMBOL '@'
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
        init_pair(1, COLOR_BLACK, COLOR_CYAN); // bird
        init_pair(2, COLOR_GREEN, COLOR_GREEN); // pipes
        init_pair(3, COLOR_WHITE, COLOR_BLACK); // score
        init_pair(4, COLOR_WHITE, COLOR_CYAN);  // background
        init_pair(5, COLOR_RED, COLOR_BLACK);   // game over
    }
    bkgd(COLOR_PAIR(4)); // Set background color to white
    clear();
    refresh();
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
    int floor_y = rows - ROUND(((float)rows/WORLD_HEIGHT)*(FLOOR_HEIGHT)) - 1;
    game_to_screen_xy(cols, rows, game->bird.x, game->bird.y, &bx, &by);

    erase();

    char BIRD_SYMBOL = DEFAULT_BIRDSYMBOL; 
    //We can add conditional for changing bird skin
    if (game->bird.velocity < -1.0f) {
        BIRD_SYMBOL = '^'; // flying up
    } else if (game->bird.velocity > 1.0f) {
        BIRD_SYMBOL = 'v'; // falling
    } else {
        BIRD_SYMBOL = '~'; // gliding
    }

    
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

    // Draw the floor
    attron(COLOR_PAIR(5));
    for(int i=floor_y; i<rows; i++){
        mvhline(i, 0, ' ', cols);
    }
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(2));
    for(int i = 0; i<MAX_PIPES; i++){
        Pipe pipe = game->pipes[i];
        if(pipe.active){
            game_to_screen_xy(cols, rows, pipe.x, pipe.gap_y, &pipe_x, &pipe_gap_y);
            for(int j = 0; j<floor_y; j++){
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
    erase();

    // Set colors for title
    attron(COLOR_PAIR(1));

    // Center "Flappy Bird" title
    const char *title = "FLAPPY BIRD";
    int title_row = rows / 3;
    int title_col = (cols - 12) / 2;
    mvprintw(title_row, title_col, "%s", title);
   

    attroff(COLOR_PAIR(1));

    // Instructions
    attron(COLOR_PAIR(3));
    const char *instr = "Press SPACE to start playing";
    int instr_row = title_row + 6;
    int instr_col = (cols - 29) / 2;
    mvprintw(instr_row, instr_col, "%s", instr);
    attroff(COLOR_PAIR(3));

    refresh();
}

void render_gameover(const GameState* game){
    erase();

    // Set colors for game over
    attron(COLOR_PAIR(5));

    // Center "GAME OVER!" title
    const char *title = "GAME OVER!";
    int title_row = rows / 3;
    int title_col = (cols - 11) / 2;
    mvprintw(title_row, title_col, "%s", title);


    // Custom message: (name), you lose
    char lose_msg[32];
    snprintf(lose_msg, sizeof(lose_msg), "%s, you lose", game->username);
    int msg_row = title_row + 2;
    int msg_col = (cols - 14) / 2;
    mvprintw(msg_row, msg_col, "%s", lose_msg);

    attroff(COLOR_PAIR(5));

    // Instructions
    attron(COLOR_PAIR(3));
    const char *instr = "Press SPACE to play again";
    int instr_row = title_row + 4;
    int instr_col = (cols - 26) / 2;
    mvprintw(instr_row, instr_col, "%s", instr);
    attroff(COLOR_PAIR(3));

    refresh();
}

void input_get_nickname(GameState *nickname) {
    int pos = 0;
    char letters[3] = {'A', 'A', 'A'};
    int done = 0;

    while (!done) {
        // Render nickname input
        erase();
        mvprintw(5, 10, "Enter your nickname:");
        for (int i = 0; i < 3; i++) {
            if (i == pos) attron(A_REVERSE);
            mvprintw(7, 10 + i * 2, "%c", letters[i]);
            if (i == pos) attroff(A_REVERSE);
        }
        mvprintw(9, 10, "Use arrows to select/change. Enter to confirm.");
        refresh();

        int ch = getch();
        switch (ch) {
            case KEY_LEFT:
                if (pos > 0) pos--;
                break;
            case KEY_RIGHT:
                if (pos < 2) pos++;
                break;
            case KEY_UP:
                if (letters[pos] < 'Z') letters[pos]++;
                break;
            case KEY_DOWN:
                if (letters[pos] > 'A') letters[pos]--;
                break;
            case '\n': // Enter
            case KEY_ENTER:
                done = 1;
                break;
        }
    }
    // Save nickname
    nickname->username[0] = letters[0];
    nickname->username[1] = letters[1];
    nickname->username[2] = letters[2];
    nickname->username[3] = '\0';

}