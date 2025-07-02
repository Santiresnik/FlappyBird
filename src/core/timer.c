#include "timer.h"
#include <time.h>

double get_current_time() {
    // clock() returns CPU time used by the program
    // CLOCKS_PER_SEC gives number of ticks per second
    return (double)clock() / CLOCKS_PER_SEC;
}