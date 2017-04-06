CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags libxml-2.0`
OUT = program
OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
LIBS = `pkg-config --libs libxml-2.0`

all : $(OBJS)
	$(CC) $(OBJS) -o $(OUT) $(CFLAGS) $(LIBS)

program.o : program.c interface.h
	$(CC) $(CFLAGS) -c program.c $(LIBS)

interface.o : interface.c articles.h contributors.h interface.h
	$(CC) $(CFLAGS) -c interface.c $(LIBS)

avl.o : avl.c avl.h
	$(CC) $(CFLAGS) -c avl.c $(LIBS)

articles.o : articles.c avl.h articles.h
	$(CC) $(CFLAGS) -c articles.c $(LIBS)

contributors.o : contributors.c avl.h contributors.h
	$(CC) $(CFLAGS) -c contributors.c $(LIBS)

clean:
	rm -f *.o $(OUT)