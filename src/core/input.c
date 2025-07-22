#include "input.h"
#ifdef WINDOWS
#include "../platform/windows/render_windows.h"
#endif

#ifdef LINUX
#include "../platform/linux/render_linux.h"
#endif

InputAction input_poll(void){
#ifdef WINDOWS
    return input_poll_windows();
#endif

#ifdef LINUX
    return input_poll_linux();
#endif
}