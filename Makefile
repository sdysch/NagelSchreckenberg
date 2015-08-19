CC=g++
CFLAGS=-std=c++11

all: main functions
	$(CC) $(CFLAGS) obj/main.o obj/functions.o -o cars

main: main.cpp functions.cpp functions.h
	mkdir -p obj
	$(CC) $(CFLAGS) -c main.cpp -o obj/main.o

functions: functions.cpp functions.h
	mkdir -p obj
	$(CC) $(CFLAGS) -c functions.cpp -o obj/functions.o

clean:
	rm cars
	rm -r obj
