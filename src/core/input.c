#ifndef WINDOWS
#ifndef LINUX
#error Either LINUX or WINDOWS must be defined
#endif
#endif

#ifdef WINDOWS
#ifndef LINUX
#include "../platform/windows/input_windows.h"
#else
#error LINUX and WINDOWS can't be defined simultaneously
#endif
#endif

#ifdef LINUX
#ifndef WINDOWS
#include "../platform/linux/input_linux.h"
#else
#error LINUX and WINDOWS can't be defined simultaneously
#endif
#endif

#include "input.h"

InputAction input_poll(void){
#ifdef WINDOWS
#ifndef LINUX
    return input_poll_windows();
#else
#error LINUX and WINDOWS can't be defined simultaneously
#endif
#endif

#ifdef LINUX
#ifndef WINDOWS
    return input_poll_linux();
#else
#error LINUX and WINDOWS can't be defined simultaneously
#endif
#endif
}