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
echo "OSTYPE=	$PLATFORM" > $file_name
echo 'CC=g++' >> $file_name
echo 'CFLAGS=-c -Wall' >> $file_name
echo 'LDFLAGS=' >> $file_name
if [[ "$PLATFORM" == 'Windows' ]]; then
	echo 'LIBS=	-lws2_32' >> $file_name
else
	echo 'LIBS=	-lpthread' >> $file_name
fi
echo "SOURCES=	$sources" >> $file_name
echo 'OBJECTS=$(SOURCES:.cpp=.o)' >> $file_name
if [[ "$PLATFORM" == 'Windows' ]]; then
	echo 'EXECUTABLE=Release/GameServer.exe' >> $file_name
else
	echo 'EXECUTABLE=Release/GameServer' >> $file_name
fi

echo 'all: $(SOURCES) $(EXECUTABLE)' >> $file_name
echo '$(EXECUTABLE): $(OBJECTS)' >> $file_name
echo '	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)' >> $file_name
echo '.cpp.o:' >> $file_name
echo '	$(CC) $(CFLAGS) $< -o $@' >> $file_name
echo 'clean:' >> $file_name
echo '	@rm -rf *.o $(EXECUTABLE) Makefile' >> $file_name
echo 'Done. Now you can type `make`.'
