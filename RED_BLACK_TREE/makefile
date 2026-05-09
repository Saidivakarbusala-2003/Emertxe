rbt.exe : main.o insert.o delete.o delete_max.o delete_min.o search.o rbt.o find_max.o find_min.o
	gcc -o rbt.exe main.o insert.o delete.o delete_max.o delete_min.o search.o rbt.o find_max.o find_min.o

main.o : main.c
	gcc -c main.c

insert.o : insert.c
	gcc -c insert.c

delete.o : delete.c
	gcc -c delete.c

delete_max.o : delete_max.c
	gcc -c delete_max.c

delete_min.o : delete_min.c
	gcc -c delete_min.c

search.o : search.c
	gcc -c search.c

rbt.o : rbt.c
	gcc -c rbt.c

find_max.o : find_max.c
	gcc -c find_max.c

find_min.o : find_min.c
	gcc -c find_min.c

clean :
	rm -f *.o *.exe