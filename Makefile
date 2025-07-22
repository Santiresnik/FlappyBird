CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Icore

SRC_CORE = core/config.c
core/game.c
core/input.c
core/physics.c
core/render.c
core/timer.c

OBJ_CORE = $(SRC_CORE:.c=.o)

BIN = flappybird
MAIN = main.c

.PHONY: all clean run

all: $(BIN)

$(BIN): $(OBJ_CORE) $(MAIN)
$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
$(CC) $(CFLAGS) -c $< -o $@

run: $(BIN)
./$(BIN)

clean:
rm -f $(OBJ_CORE) $(BIN)