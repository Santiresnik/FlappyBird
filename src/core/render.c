#include "render.h"
#include "curses_wrapper.h"
#include "input.h"
#include <string.h>

#define HEART "<3 "
#define DEFAULT_BIRDSYMBOL '@'
#define PIPE_SYMBOL ' '
#define BIRD_UP '^'
#define BIRD_DOWN 'v'
#define BIRD_GLIDE '~'

#define MAP(ix, il, ih, ol, oh) ((ol) + (((ix)-(il))*((oh)-(ol)))/((ih)-(il)))
#define ROUND(x) (((x) - (int)(x)) >= 0.5f ? (int)(x) + 1 : (int)(x))

static void game_to_screen_xy(int rows, int cols, float gx, float gy, int* psx, int* psy);

static int rows;
static int cols;

void render_init(void) {
    initscr();            // Start curses mode
    cbreak();             // Disable line buffering
    noecho();             // Don’t echo pressed keys
    keypad(stdscr, TRUE); // Enable special keys (arrows, etc.)
    nodelay(stdscr, TRUE); // Non-blocking input
    curs_set(0);          // Hide cursor
    getmaxyx(stdscr, rows, cols);
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_CYAN); // bird
        init_pair(2, COLOR_GREEN, COLOR_GREEN); // pipes
        init_pair(3, COLOR_BLACK, COLOR_WHITE); // score
        init_pair(4, COLOR_WHITE, COLOR_CYAN);  // background
        init_pair(5, COLOR_RED, COLOR_BLACK);   // game over
    }
    bkgd(COLOR_PAIR(4)); // Set background color to white
    erase();
    refresh();
}

void render_shutdown(void) {
    // Undo modes in reverse order
    nodelay(stdscr, FALSE);
    keypad(stdscr, FALSE);
    nocbreak();
    echo();
    curs_set(1);

    if (!isendwin()) {
        endwin();
    }
}

void render_draw(const GameState* game){
    const char * txt;
    int bx, by, pipe_x, pipe_gap_y;
    int pipe_width = ROUND(((float)cols/WORLD_WIDTH)*(game->config.pipe_width));
    int pipe_gap_height = ROUND(((float)rows/WORLD_HEIGHT)*(game->config.pipe_gap_height));
    int floor_y = rows - ROUND(((float)rows/WORLD_HEIGHT)*(FLOOR_HEIGHT)) - 1;
    game_to_screen_xy(cols, rows, game->bird.x, game->bird.y, &bx, &by);

    erase();

    char BIRD_SYMBOL = DEFAULT_BIRDSYMBOL; //TODO: select bird symbol

    if (game->bird.velocity < -1.0f) {
        BIRD_SYMBOL = BIRD_UP;
    } else if (game->bird.velocity > 1.0f) {
        BIRD_SYMBOL = BIRD_DOWN;
    } else {
        BIRD_SYMBOL = BIRD_GLIDE;
    }


    attron(COLOR_PAIR(1));
    if (game->collision_timer > 0) {
        // Blink for grace period
        if (((int)(game->collision_timer * 10)) % 2 == 0) { 
            mvaddch(by, bx, BIRD_SYMBOL);
        }
    } 
    else {
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
    txt = "Score: ";
    attron(COLOR_PAIR(3));
    mvprintw(0, (int)(cols*0.9f), "%s%d",txt, game->score);
    attroff(COLOR_PAIR(3));

    //Draw lives
    txt = "Lives: ";
    attron(COLOR_PAIR(3));
    mvprintw(0, 0, "%s", txt);  // Position top-left corner
    for (int i = 0; i < game->lives; i++) {
        mvprintw(0, strlen(txt) + i*strlen(HEART), HEART);  // Print hearts with spacing
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
    const char *txt = "FLAPPY BIRD";
    int title_col = (cols - strlen(txt)) / 2;
    mvprintw(rows/3, title_col, "%s", txt);


    attroff(COLOR_PAIR(1));

    // Instructions
    attron(COLOR_PAIR(3));
    txt = "Press SPACE to start playing";
    int instr_col = (cols - strlen(txt)) / 2;
    mvprintw(rows/2, instr_col, "%s", txt);
    attroff(COLOR_PAIR(3));

    refresh();
}

void render_gameover(const GameState* game){
    erase();

    // Set colors for game over
    attron(COLOR_PAIR(5));

    // Center "GAME OVER!" title
    const char *txt = "GAME OVER!";
    int title_col = (cols - strlen(txt)) / 2;
    mvprintw(rows/3, title_col, "%s", txt);

    // Custom message: (name), you lose
    txt = ", you lose";
    int msg_row = rows/2;
    int msg_col = (cols - strlen(txt) - strlen(game->username)) / 2;
    mvprintw(msg_row, msg_col, "%s%s", game->username, txt);

    attroff(COLOR_PAIR(5));
    attron(COLOR_PAIR(3));

    // Show score below lose message
    char score_msg[32];
    snprintf(score_msg, sizeof(score_msg), "Score: %d", game->score);

    int score_row = msg_row + 2;
    int score_col = (cols - strlen(score_msg)) / 2;
    mvprintw(score_row, score_col, "%s", score_msg);

    //Highscore
    HighScore scores[MAX_SCORES];
    int num_scores = read_high_scores(scores, MAX_SCORES);

    attron(COLOR_PAIR(3));
    txt = "=== HIGH SCORES ===";
    int scores_row = score_row +3;
    mvprintw(scores_row, (cols - strlen(txt)) / 2, txt);
    for (int i = 0; i < num_scores; i++) {
        mvprintw(scores_row + i + 1, (cols-16)/2, "%d. %s - %d", i+1, scores[i].name, scores[i].score);
    }
    attroff(COLOR_PAIR(3));

    // Instructions
   
    txt = "Press SPACE to play again";
    int instr_row = score_row + 2;
    int instr_col = (cols - strlen(txt)) / 2;
    mvprintw(instr_row, instr_col, "%s", txt);
    attroff(COLOR_PAIR(3));

    refresh();
}

void render_nickname(const NicknameState* state) {
    erase();
    const char * txt = "Enter your nickname:";
    mvprintw(rows/4, cols/3, txt);
    for (int i = 0; i < MAX_USERNAME_LEN; i++) {
        if (i == state->pos) attron(A_REVERSE);
        mvprintw((rows/4)+2, (cols/3) + i*2, "%c", state->letters[i]);
        if (i == state->pos) attroff(A_REVERSE);
    }
    txt = "Use arrows to select/change. Enter to confirm.";
    mvprintw((rows/4)+4, cols/3, txt);
    refresh();
}
