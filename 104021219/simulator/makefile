CC0 = g++ -std=c++11 -O3 -Wall
CC = g++ -std=c++11 -g -Wall
OBJ = main.o memory.o irfile.o
archiTA = ../../archiTA
goldensim = $(archiTA)/simulator/single_cycle
testcase = $(archiTA)/testcase/open_testcase

all: single_cycle

single_cycle: ${OBJ}
	$(CC) -o single_cycle $^

%.o: %.cpp
	$(CC) -c $^

.PNOHY: run
run: clean golden single_cycle
	./single_cycle
	diff snapshot.rpt diff/snapshot.rpt || exit 0
	diff error_dump.rpt diff/error_dump.rpt || exit 0

.PNOHY: golden
golden: dimage.bin iimage.bin
	./$(goldensim)
	mv *.rpt diff/

.PNOHY: test
test: clean single_cycle
test: opentest-branch opentest-fib_dp opentest-func opentest-mult opentest-recur
	echo 'Finish Test!!!'

opentest-%: single_cycle
	cp $(testcase)/$(subst opentest-,,$@)/*.bin .
	./$(goldensim)
	mv *.rpt diff/
	./single_cycle
	diff snapshot.rpt diff/snapshot.rpt
	diff error_dump.rpt diff/error_dump.rpt

.PHONY: clean
clean:
	rm -f single_cycle *.o *.rpt
