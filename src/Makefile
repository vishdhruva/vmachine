GCC = gcc -std=c99 -g
VAL = valgrind --tool=memcheck --log-file=vallog --leak-check=full --verbose

SRCS = main.c
OBJS = $(SRCS:%.c=%.o)

vmachine: $(OBJS)
	$(GCC) $(OBJS) -o vmachine

.c.o:
	$(GCC) -c $*.c

memory: vmachine
	$(VAL) ./vmachine

clean: # remove all machine generated files
	rm -f vmachine *.o output? vallog testgen
