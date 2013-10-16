CC=gcc
INCLUDES=
CFLAGS=gcc
OBJS := thread_create.o
OUTPUT := thread_create

all:$(OBJS)
	$(CC) $(OBJS) -o $(OUTPUT)

$(OBJS):thread_create.c
	$(CC) -c -o $@ $<

.PHONY:clean

clean:
	rm *.o $(OUTPUT)





