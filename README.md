# FlappyBird

A terminal-based version of the classic Flappy Bird, written in C with portability in mind. This project separates platform-independent game logic from platform-specific input/output layers, making it easy to compile on both Linux and Windows.

📚 Libraries

This project uses Ncurses library for both Windows and Linux. This is a library for building text-based user interfaces in a terminal. You’ll need it installed before compiling and running this project.

Linux bash commands (Ubuntu):

    sudo apt update

    sudo apt install libncurses5-dev libncursesw5-dev

Windows:

[Link to PDCurses (equivalent of ncurses for CodeBlocks)](https://pdcurses.org/)


📁 Project Structure

The source files are organized in the src/ directory:

src/
├── core/ → Platform-independent game logic

│ ├── config.[ch] → Constants and default parameters (e.g. gravity, jump force)

│ ├── curses_wrapper.h  → Headers for ncurses and pdcurses library

│ ├── game.[ch] → Main game state logic and update loop

│ ├── input.[ch] → Abstract input interface

│ ├── physics.[ch] → Gravity, velocity, collisions

│ ├── render.[ch] → Abstract rendering interface

│ ├── render.[ch] → ASCII rendering with curses

│ ├── timer.[ch] → Frame timing, FPS handling

├── main.c → Entry point, handles initialization & game loop

├── Makefile → Linux build script

├── FlappyBird.cbp → Code::Blocks project file for Windows

├── .gitignore → Ignore build files, binaries, and Code::Blocks cache

└── README.md → You are here!
