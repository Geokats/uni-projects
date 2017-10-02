SOURCE	= indent.c
HEADER  = 
OBJS 	= indent.o
OUT  	= indent
CC		= gcc
FLAGS   = -g -c

# -g option enables debugging mode 
# -c flag generates object code for separate files

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT)
	rm -f $(OBJS)

indent.o: indent.c
	$(CC) $(FLAGS) indent.c

clean:
	rm -f $(OUT)

count:
	wc $(SOURCE) $(HEADER)