CC=g++
CFLAGS=-c -Wall -lncurses
LDFLAGS=-lncurses
SOURCES=main.cc utilities.cc junk.cc usable.cc alcohol.cc armor.cc weapon.cc player.cc level.cc game.cc graphics.cc enemy.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=game

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
	rm $(EXECUTABLE)


