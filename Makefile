all:
	gcc main.c globals.c init.c ship.c enemy.c defense.c bullet.c collision.c score.c lives.c -lSDL2 -lSDL2_mixer
