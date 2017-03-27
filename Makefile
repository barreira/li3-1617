CC = gcc
CFLAGS= -Wall -g `pkg-config --cflags libxml-2.0`
OBJS=$(patsubst %.c, %.o, $(wildcard *.c))
LIBS = `pkg-config --libs libxml-2.0`
all: $(OBJS)
	    $(CC) $(CFLAGS) -o program $(OBJS) $(LIBS)
clean:
	    rm program *.o