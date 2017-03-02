CC=g++ -std=c++11 -O3 -Wall

single_cycle: main.o memory.o
	$(CC) -o single_cycle main.o memory.o

main.o: main.cpp
	$(CC) -c main.cpp

memory.o: memory.cpp
	$(CC) -c memory.cpp

.PNOHY: clean

clean:
	rm -f single_cycle *.o
