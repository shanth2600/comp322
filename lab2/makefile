EXECUTABLES=launch tube
	tube_SRC = tube.c
	tube_OBJ = tube.o

	launch_SRC = launch.c
	launch_OBJ = launch.o

CC = gcc
CFLAGS = -g

all: launch tube

launch: launch.c
	gcc -o launch launch.c
tube: tube.c
	gcc -o tube tube.c



clean:
	rm -f $(EXECUTABLES) $(OBJ) *~v
	rm -f $(EXECUTABLES) $(OBJ) *~
