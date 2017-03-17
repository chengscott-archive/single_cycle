CC0 = g++ -std=c++11 -O3 -Wall
CC = g++ -std=c++11 -g -Wall
OBJ = main.o memory.o irfile.o
archiTA = ../../archiTA
goldensim = $(archiTA)/simulator/single_cycle
testcase = $(archiTA)/testcase/open_testcase

all: clean single_cycle run

single_cycle: ${OBJ}
	$(CC) -o single_cycle $^

%.o: %.cpp
	$(CC) -c $^

.PNOHY: run
run: golden single_cycle
	./single_cycle
	diff snapshot.rpt diff/snapshot.rpt || exit 0
	diff error_dump.rpt diff/error_dump.rpt || exit 0

.PNOHY: golden
golden: dimage.bin iimage.bin
	./$(goldensim)
	mv *.rpt diff/

.PNOHY: test
test: test-branch test-fib_dp test-func test-mult test-recur
	echo 'Finish Test!!!'

test-%: single_cycle
	cp $(testcase)/$(subst test-,,$@)/*.bin .
	./$(goldensim)
	mv *.rpt diff/
	./single_cycle
	diff snapshot.rpt diff/snapshot.rpt || exit 0
	diff error_dump.rpt diff/error_dump.rpt || exit 0
	rm *.bin

.PHONY: clean
clean:
	rm -f single_cycle *.o *.rpt
