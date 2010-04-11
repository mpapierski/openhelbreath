PLATFORM='Unknown'
if [[ "$OSTYPE" == 'linux-gnu' ]]; then
	PLATFORM='Linux'
elif [[ "$OSTYPE" == 'msys' ]]; then
	PLATFORM='Windows'
fi

echo "Generating Makefile for $PLATFORM..."
sources=`ls *.cpp | sed ':start /^.*$/N;s/\n/ /g; t start'`
file_name="Makefile"
touch "$file_name"
echo "OSTYPE=$PLATFORM" > $file_name

if [[ "$OSTYPE" == 'linux-gnu' ]]; then
	echo 'CC=g++' >> $file_name
elif [[ "$OSTYPE" == 'msys' ]]; then
	echo 'CC=mingw32-g++' >> $file_name
fi

echo 'CFLAGS=-Wall -O2 `sdl-config --cflags`' >> $file_name
echo 'LDFLAGS=' >> $file_name
if [[ "$PLATFORM" == 'Windows' ]]; then
	echo 'LIBS=`sdl-config --libs` -lSDL_image -lSDL_ttf -lSDL_mixer -lws2_32' >> $file_name
else
	echo 'LIBS=`sdl-config --libs` -lSDL_image -lSDL_ttf -lSDL_mixer' >> $file_name
fi
echo "SOURCES=$sources" >> $file_name
echo 'OBJECTS=$(SOURCES:.cpp=.o)' >> $file_name
echo "$OBJECTS"

if [[ "$PLATFORM" == 'Windows' ]]; then
	echo 'EXECUTABLE=Release/HelGame.exe' >> $file_name
else
	echo 'EXECUTABLE=Release/HelGame' >> $file_name
fi

echo 'all: $(SOURCES) $(EXECUTABLE)' >> $file_name
echo '$(EXECUTABLE): $(OBJECTS)' >> $file_name
echo '	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ -s $(LIBS) ' >> $file_name
echo '.cpp.o:' >> $file_name
echo '	$(CC) $(CFLAGS) -c $< -o $@' >> $file_name
echo 'clean:' >> $file_name
echo '	@rm -rf $(OBJECTS) $(EXECUTABLE)' >> $file_name
echo 'Done. Now you can type `make`.'
