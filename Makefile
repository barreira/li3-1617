CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags libxml-2.0`
OUT = program
OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
LIBS = `pkg-config --libs libxml-2.0`

program : interface
	$(CC) $(CFLAGS) program.c -o program $(LIBS) interface.o

interface : contributors articles
	$(CC) $(CFLAGS) -c interface.c $(LIBS) contributors.o articles.o

xmlparser : interface avl contributors articles
	$(CC) $(CFLAGS) -c xmlparser.c $(LIBS) interface.o avl.o contributors.o articles.o

avl :
	$(CC) $(CFLAGS) -c avl.c $(LIBS)

articles : avl
	$(CC) $(CFLAGS) -c articles.c $(LIBS) avl.o

contributors : avl
	$(CC) $(CFLAGS) -c contributors.c $(LIBS) avl.o

clean:
	rm -f *.o $(OUT)