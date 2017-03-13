CC0 = g++ -std=c++11 -O3 -Wall
CC = g++ -std=c++11 -g -Wall
OBJ = main.o memory.o irfile.o

single_cycle: ${OBJ}
	$(CC) -o single_cycle $^

%.o: %.cpp
	$(CC) -c $^

.PNOHY: run
run:
	./single_cycle
	diff snapshot.rpt diff/snapshot.rpt || exit 0
	diff error_dump.rpt diff/error_dump.rpt || exit 0

.PNOHY: golden
golden:
	./../../archiTA/simulator/single_cycle
	mv *.rpt diff/

.PHONY: clean
clean:
	rm -f single_cycle *.o *.rpt
