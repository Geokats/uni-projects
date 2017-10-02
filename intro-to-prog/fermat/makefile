SOURCE	= fermat.c
HEADER  = 
OBJS 	= fermat.o 
OUT  	= fermat
CC		= gcc
FLAGS   = -g -c 

# -lm option link math library
# -g option enables debugging mode 
# -c flag generates object code for separate files

fermat: $(OBJS)
	$(CC) $(OBJS) -lm -o $(OUT)
	rm -f $(OBJS)

fermat.o: fermat.c
	$(CC) $(FLAGS) fermat.c

clean:
	rm -f $(OUT)

count:
	wc $(SOURCE) $(HEADER)