CC=gcc
CFLAGS=`sdl-config --cflags --libs`
SOURCES=*.c
OPX=opx/*.c
OBJECTS=obj/*.o
main : obj/main.o obj/opx.o
	$(CC) $(OBJECTS) -o main $(CFLAGS)

obj/main.o : $(SOURCES)
	$(CC) $(SOURCES) -c -o obj/main.o $(CFLAGS)

obj/opx.o : $(OPX)
	$(CC) $(OPX) -c -o obj/opx.o $(CFLAGS)

clear :
	rm $(OBJECTS)

clear_main :
	rm main
