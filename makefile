CC=gcc
CFLAGS=`sdl-config --cflags --libs`
SOURCES:=$(wildcard *.c)
OPX:=$(wildcard opx/*.c)
OBJECTS:=$(wildcard obj/*.o)
OBJECTS_OPX:=$(wildcard *.o)

first : obj screenshots
	mkdir obj
	mkdir screenshots

main : main_ opx_
	$(CC) $(OBJECTS) -o main $(CFLAGS)

main_ : $(SOURCES)
	$(CC) $(SOURCES) -c $(CFLAGS)

opx_ : $(OPX)
	$(CC) $(OPX) -c $(CFLAGS)
	@mv *.o obj/

.PHONY : clean clean_main
clean :
	rm $(OBJECTS)

clean_main :
	rm main
