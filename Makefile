CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cc junk.cc consumable.cc alcohol.cc level.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=TheGame

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	g++ $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(EXECUTABLE)
	rm *.o


