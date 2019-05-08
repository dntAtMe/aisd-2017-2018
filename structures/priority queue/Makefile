.phony: all clean

all: main

main: main.o
	$(CXX) -std=c++14 -o $@ $+

main.o: main.cpp prioqueue.cpp prioqueue.h 
	$(CXX) -std=c++14 -c -o $@ $<

clean:
	rm -f *.o main
