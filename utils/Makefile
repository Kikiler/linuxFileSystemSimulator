obj = tests.o linkedList.o
tests.out: $(obj) 
	cc $^ -o $@ -g 
%.o: %.c
	cc -c $^ -Wall -Wextra -g -o $@
.PHONY:  run clean
run:
	./tests.out

clean:
	rm -v -f *.o 
	rm -v -f *.out 
