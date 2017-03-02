CC=g++ -std=c++11 -O3 -Wall

single_cycle: main.o
	$(CC) -o single_cycle main.o

main.o: main.cpp
	$(CC) -c main.cpp

.PNOHY: clean

clean:
	rm -f single_cycle *.o
