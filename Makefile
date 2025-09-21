utils = utils/linkedList.o
obj = main.o commands.o $(utils)
tests = commands.o tests.o $(utils)
simulator.out: $(obj) 
	cc $^ -o $@ -g
%.o: %.c
	cc -c $^ -Wall -Wextra -g -o $@
$(utils) : utils/linkedList.c
	cc -c $^ -Wall -Wextra -g -o $@

.PHONY: clean
run: simulator.out
	./simulator.out
	make clean


test: tests.out
tests.out : $(tests)
	cc $^ -o $@ -g

runTest:tests.out
	./tests.out
	make clean


clean:
	rm -v -f *.o 
	rm -v -f *.out 
