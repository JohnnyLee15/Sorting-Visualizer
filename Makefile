RAYLIB_CFLAGS := $(shell pkg-config --cflags raylib)
RAYLIB_LIBS   := $(shell pkg-config --libs raylib)

all: main

main: main.o visualizer.o sort_logs.o arrayFunctions.o algoRegistry.o
	clang -Wall main.o visualizer.o sort_logs.o arrayFunctions.o algoRegistry.o -o main $(RAYLIB_LIBS)

main.o: main.c visualizer.h algoRegistry.h
	clang -Wall -c main.c -o main.o

algoRegistry.o: algoRegistry.c algoRegistry.h sort_logs.h
	clang -Wall -c algoRegistry.c -o algoRegistry.o

visualizer.o: visualizer.c visualizer.h sort_logs.h algoRegistry.h arrayFunctions.h
	clang -Wall -c visualizer.c -o visualizer.o $(RAYLIB_CFLAGS)

sort_logs.o: sort_logs.c sort_logs.h arrayFunctions.h
	clang -Wall -c sort_logs.c -o sort_logs.o

arrayFunctions.o: arrayFunctions.c arrayFunctions.h
	clang -Wall -c arrayFunctions.c -o arrayFunctions.o

clean:
	rm -f main.o visualizer.o sort_logs.o arrayFunctions.o algoRegistry.o main
