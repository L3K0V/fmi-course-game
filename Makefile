CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cc junk.cc usable.cc alcohol.cc armor.cc weapon.cc player.cc level.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=TheGame

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
	rm $(EXECUTABLE)


