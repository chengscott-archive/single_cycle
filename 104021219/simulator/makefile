CC = g++ -std=c++11 -O3 -Wall
OBJ = main.o memory.o irfile.o regfile.o

single_cycle: ${OBJ}
	$(CC) -o single_cycle $^

%.o: %.cpp
	$(CC) -c $^

.PNOHY: clean

clean:
	rm -f single_cycle *.o
