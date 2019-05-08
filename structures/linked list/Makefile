CC=gcc
CFLAGS=-Wall
DEPS=task2.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
task2: task2.o
	gcc -o task2 task2.c  $(CFLAGS)

clean:
	rm -f *.o task2
