Address.exe : main.o contact.o file.o validate.o populate.o
	gcc -o Address.exe main.o contact.o file.o validate.o populate.o
main.o : main.c
	gcc -c main.c
contact.o : contact.c
	gcc -c contact.c
file.o : file.c
	gcc -c file.c
validate.o : validate.c
	gcc -c validate.c
populate.o : populate.c
	gcc -c populate.c
clean :
	rm *.exe *.o
