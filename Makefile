obj = main.o commands.o
simulator.out: $(obj) 
	cc $^ -o $@ -g 
%.o: %.c
	cc -c $^ -Wall -Wextra -g -o $@
.PHONY:  run clean
run:
	./simulator.out

clean:
	rm -v -f *.o 
	rm -v -f *.out 
