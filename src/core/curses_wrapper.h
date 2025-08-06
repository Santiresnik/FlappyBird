#ifndef CURSES_WRAPPER_H
#define CURSES_WRAPPER_H

#ifndef WINDOWS
#ifndef LINUX
#error "Either LINUX or WINDOWS must be defined"
#endif
#endif

#ifdef WINDOWS
#ifndef LINUX
#include <curses.h>
#else
#error "LINUX and WINDOWS can't be defined simultaneously"
#endif
#endif  

#ifdef LINUX
#ifndef WINDOWS
#include <ncurses.h>
#else
#error "LINUX and WINDOWS can't be defined simultaneously"
#endif
#endif
#endif