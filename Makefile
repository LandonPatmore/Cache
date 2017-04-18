#Makefile
CC     = gcc
CFLAGS = -g
LFLAGS =
OBJS   = cache.o
EXEC   = program
LIBS  =
INCS  =

$(EXEC)   :   $(OBJS)
	$(CC) $(LFLAGS) -o $(EXEC) $(OBJS) $(LIBS) -lm

.c.o:
	$(CC) $(CFLAGS) -c $(INCS) $*.c

clean :
	rm -f $(EXEC) $(OBJS)
