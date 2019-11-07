# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
CFLAGS = -Wall -Wextra -pedantic -Werror

all: cellularAutomaton.o
	$(CC) $(CFLAGS) -o cellularAutomaton cellularAutomaton.o

cellularAutomaton.o: cellularAutomaton.c cellularAutomaton.h
	$(CC) $(CFLAGS) -c cellularAutomaton.c
	
clean:
	rm -rf *.o 
