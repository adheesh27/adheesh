CFLAGS = -g -Wall -O2 `pkg-config --cflags gtk+-2.0 gthread-2.0`
LIBS = `pkg-config --libs gtk+-2.0 gthread-2.0`
CC = gcc
OBJS = generator.o solver.o sudoku.o

all: sudoku

sudoku: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o project

generator.o: generator.c generator.h sudoku.h
	$(CC) $(CFLAGS) -c generator.c

solver.o: solver.c solver.h sudoku.h
	$(CC) $(CFLAGS) -c solver.c

sudoku.o: sudoku.c sudoku.h solver.h generator.h
	$(CC) $(CFLAGS) -c sudoku.c

clean:
	/bin/rm -f $(OBJS)
