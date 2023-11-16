CC = gcc
CFLAGS = -Wall -lmenu -lncurses -I$(IDIR) -g
CFLAGS = -lncurses -lm -I./include/

IDIR = ./include/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c\
		  $(SRCDIR)mineFiles/*.c

all: rogue run clean

rogue: $(SOURCES)
	$(CC) -Wall $(SOURCES) -o $@ $(CFLAGS)

run:
	./rogue

clean:
	rm rogue