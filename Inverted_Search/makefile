Inv.sec : main.o create.o display.o inverted.o search.o save.o update.o
	gcc -o Inv.sec main.o create.o display.o inverted.o search.o save.o update.o
main.o : main.c
	gcc -c main.c
apc.o : create.c
	gcc -c create.c
add.o : display.c
	gcc -c display.c
sub.o : inverted.c
	gcc -c inverted.c
mul.o : search.c
	gcc -c search.c
div.o : save.c
	gcc -c save.c
modu.o : update.c
	gcc -c update.c
	
clean :
	rm *.exe *.o