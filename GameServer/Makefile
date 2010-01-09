CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=Application.cpp GameServer.cpp IniFile.cpp Map.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=GameServer

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	@rm -rf *.o $(EXECUTABLE)
