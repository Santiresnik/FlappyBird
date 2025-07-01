FlappyBird: main.o game.o physics.o config.o 
	gcc -Wall -g -o FlappyBird main.o game.o physics.o config.o
main.o: main.c game.h 
	gcc -Wall -g main.c

game.o: game.c game.h physics.h config.h
	gcc -Wall -g game.c

physics.o: physics.c physics.h
	gcc -Wall -g physics.c

config.o: config.c config.h
	gcc -Wall -g config.c
