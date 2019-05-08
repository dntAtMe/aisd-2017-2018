CC=gcc
CFLAGS=-Wall
DEPS=task1.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
task1: task1.o
	gcc -o task1 task1.c $(CFLAGS)

clean:
	rm -f *.o task1
