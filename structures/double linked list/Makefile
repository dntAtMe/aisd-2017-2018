CC=gcc
CFLAGS=-Wall
DEPS=task3.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
task3: task3.o
	gcc -o task3 task3.c $(CFLAGS)

clean:
	rm -f *.o task3
