CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags libxml-2.0`
OUT = program
OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
LIBS = `pkg-config --libs libxml-2.0`

all : $(OBJS)
	$(CC) $(OBJS) -o $(OUT) $(CFLAGS) $(LIBS)

program.o : interface.o
	$(CC) $(CFLAGS) program.c -o program $(LIBS) interface.o

interface.o : contributors.o articles.o
	$(CC) $(CFLAGS) interface.c -o interface $(LIBS) interface.o contributors.o articles.o

xmlparser.o : interface.o avl.o contributors.o articles.o
	$(CC) $(CFLAGS) interface.c -o interface $(LIBS) xmlparser.o interface.o avl.o contributors.o articles.o

avl.o :
	$(CC) $(CFLAGS) avl.c -o avl $(LIBS)

articles.o : avl.o
	$(CC) $(CFLAGS) articles.c -o articles $(LIBS) articles.o avl.o

contributors.o : avl.o
	$(CC) $(CFLAGS) contributors.c -o contributors $(LIBS) contributors.o avl.o

clean:
	rm -f *.o $(OUT)