CC=gcc
EXE=game
CFLAGS=-I.
LFLAGS=-L. -lm -lpthread -lX11 -lXrandr -lGL -lGLU -lgl2d -lglfw
OBJS=game.o player.o bubble.o harpoon.o

$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $(EXE) $(LFLAGS) 

player.o: player.c player.h common.h

bubble.o: bubble.c bubble.h common.h

hapoon.o: harpoon.c hapoon.h player.h common.h

.PHONY: clean

clean:
	rm $(OBJS) $(EXE)
