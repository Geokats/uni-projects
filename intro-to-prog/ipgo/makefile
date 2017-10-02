default : go

go : go.o  administrative.o inout.o play.o setup.o 
	gcc -o go go.o administrative.o inout.o play.o setup.o
	rm -f *.o

go.o : go.c go.h
	gcc -c go.c

administrative.o : administrative.c administrative.h
	gcc -c administrative.c

inout.o : inout.c inout.h
	gcc -c inout.c

play.o : play.c play.h
	gcc -c play.c

setup.o : setup.c setup.h
	gcc -c setup.c
clean: 
	rm -f go