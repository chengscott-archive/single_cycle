CC = g++ -std=c++11 -Ofast -Wall
CC0 = g++ -std=c++11 -g -Wall
OBJ = main.o memory.o irfile.o
archiTA = ../../archiTA
goldensim = $(archiTA)/simulator/single_cycle

all: single_cycle

single_cycle: ${OBJ}
	$(CC) -o single_cycle $^

%.o: %.cpp
	$(CC) -c $^

.PNOHY: run
run: clean golden single_cycle
	./single_cycle
	diff snapshot.rpt diff/snapshot.rpt
	diff error_dump.rpt diff/error_dump.rpt

.PNOHY: golden
golden: dimage.bin iimage.bin
	./$(goldensim)
	mv *.rpt diff/

.PNOHY: test
test: clean single_cycle
	make -f makefile.test

.PHONY: clean
clean:
	rm -f single_cycle *.o *.rpt
