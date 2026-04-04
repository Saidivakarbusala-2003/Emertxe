OBJ := $(patsubst %.c , %.o , $(wildcard *.c))
lsb.out : $(OBJ)
	gcc -o $@ $^
clean:
	rm *.out *.o