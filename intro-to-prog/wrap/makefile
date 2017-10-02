SOURCE	= wrap.c gre.c rec.c mem.c
HEADER  = 
OUT  	= wrap
CC		= gcc
FLAGS   = -g -c

# -g option enables debugging mode 
# -c flag generates object code for separate files

greedy: wrap.o gre.o
	$(CC) wrap.o gre.o -o $(OUT)
	rm -f wrap.o gre.o

recursive: wrap.o rec.o
	$(CC) wrap.o rec.o -o $(OUT)
	rm -f wrap.o rec.o

dynamic: wrap.o mem.o
	$(CC) wrap.o mem.o -o $(OUT)
	rm -f wrap.o mem.o

wrap.o: wrap.c
	$(CC) $(FLAGS) wrap.c

gre.o: gre.c
	$(CC) $(FLAGS) gre.c

rec.o: rec.c
	$(CC) $(FLAGS) rec.c

mem.o: mem.c
	$(CC) $(FLAGS) mem.c

clean:
	rm -f $(OUT)

count:
	wc $(SOURCE) $(HEADER)