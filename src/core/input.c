/*
This file provides a unified input_poll function that delegates
actual input handling to the appropriate platform-specific implementation
depending on whether the game is being compiled for Windows or Linux.

Usage:

- Ensure that either the WINDOWS or LINUX macro is defined at compile time.
- Do not define both at once, or the compilation will fail.
- Calls input_poll_windows or input_poll_linux accordingly.
- Includes error checks to prevent conflicting or missing platform definitions.

*/
#include "input.h"

#ifndef WINDOWS
#ifndef LINUX
#error "Either LINUX or WINDOWS must be defined"
#endif
#endif

#ifdef WINDOWS
#ifndef LINUX
#include "../platform/windows/input_windows.h"
#else
#error "LINUX and WINDOWS can't be defined simultaneously"
#endif
#endif

#ifdef LINUX
#ifndef WINDOWS
#include "../platform/linux/input_linux.h"
#else
#error "LINUX and WINDOWS can't be defined simultaneously"
#endif
#endif

InputAction input_poll(void){
#ifdef WINDOWS
#ifndef LINUX
    return input_poll_windows();
#else
#error "LINUX and WINDOWS can't be defined simultaneously"
#endif
#endif

#ifdef LINUX
#ifndef WINDOWS
    return input_poll_linux();
#else
#error "LINUX and WINDOWS can't be defined simultaneously"
#endif
#endif
}
