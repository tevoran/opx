CC=gcc
CFLAGS=-ggdb3 -lglib-2.0 `sdl-config --cflags --libs` `pkg-config gl --libs`  
CFLAGS_FAST=-O3 -march=native `sdl-config --cflags --libs` `pkg-config gl --libs`
SOURCES:=$(wildcard *.c)
OPX:=$(wildcard opx/*.c)
OBJECTS:=$(wildcard obj/*.o)
OBJECTS_OPX:=$(wildcard *.o)

first :
	mkdir obj
	mkdir screenshots

main : main_ opx_
	$(CC) $(OBJECTS) -o main $(CFLAGS_FAST) 

main_ : $(SOURCES)
	$(CC) $(SOURCES) -c $(CFLAGS_FAST) 

opx_ : $(OPX)
	$(CC) $(OPX) -c $(CFLAGS_FAST) 
	@mv *.o obj/

.PHONY : clean clean_main
clean :
	rm $(OBJECTS)

clean_main :
	rm main
