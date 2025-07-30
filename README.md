# FlappyBird

A terminal-based version of the classic Flappy Bird, written in C with portability in mind. This project separates platform-independent game logic from platform-specific input/output layers, making it easy to compile on both Linux and Windows.


📁 Project Structure

The source files are organized in the src/ directory:

src/
├── core/ → Platform-independent game logic

│ ├── config.[ch] → Constants and default parameters (e.g. gravity, jump force)

│ ├── game.[ch] → Main game state logic and update loop

│ ├── input.[ch] → Abstract input interface

│ ├── physics.[ch] → Gravity, velocity, collisions

│ ├── render.[ch] → Abstract rendering interface

│ ├── timer.[ch] → Frame timing, FPS handling

├── platform/windows/ → Windows-specific input/rendering

│ ├── input_windows.[ch] → Input with conio.h or ncurses for Windows

│ ├── render_windows.[ch] → ASCII rendering for Windows terminal

├── platform/linux/ → Linux-specific input/rendering

│ ├── input_linux.[ch] → Input for linux

│ ├── render_linux.[ch] → ASCII rendering for linux terminal

│
├── main.c → Entry point, handles initialization & game loop

├── Makefile → Linux build script

├── FlappyBird.cbp → Code::Blocks project file for Windows

├── .gitignore → Ignore build files, binaries, and Code::Blocks cache

└── README.md → You are here!
