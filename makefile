CC=gcc 
CFLAGS=-O3 -march=native -l OpenCL -I /opt/AMDAPP/include/ `sdl-config --cflags --libs` `pkg-config gl --libs`
SOURCES:=$(wildcard *.c) $(wildcard opx/*.c)
OBJECTS=$(patsubst %.c,obj/%.o,$(wildcard $(SOURCES)))


all : main

main : $(OBJECTS)
	[ -d obj/opx ] || mkdir -p obj/opx
	[ -d screenshots ] || mkdir screenshots
	echo $(SOURCES)
	echo $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $<

obj/%.o: %.c
obj/opx/%.o: opx/%.c
	$(CC) $(CFLAGS) -c -o $@ $<



.PHONY : clean clean_main
clean :
	rm $(OBJECTS) $(OBJECTS_OPX)

clean_main :
	rm main
