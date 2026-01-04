RAYLIB_CFLAGS := $(shell pkg-config --cflags raylib)
RAYLIB_LIBS   := $(shell pkg-config --libs raylib)

all: main

main: main.o visualizer.o sort_logs.o arrayFunctions.o
	clang -Wall main.o visualizer.o sort_logs.o arrayFunctions.o -o main $(RAYLIB_LIBS)

main.o: main.c visualizer.h
	clang -Wall -c main.c -o main.o

visualizer.o: visualizer.c visualizer.h sort_logs.h
	clang -Wall -c visualizer.c -o visualizer.o $(RAYLIB_CFLAGS)

sort_logs.o: sort_logs.c sort_logs.h arrayFunctions.h
	clang -Wall -c sort_logs.c -o sort_logs.o

arrayFunctions.o: arrayFunctions.c arrayFunctions.h
	clang -Wall -c arrayFunctions.c -o arrayFunctions.o

clean:
	rm -f main.o visualizer.o sort_logs.o arrayFunctions.o main
