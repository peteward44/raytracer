BOOST_COMPILE_FLAGS=-I/projects/local/work/boost/
BOOST_LINK_FLAGS=-lboost_signals-gcc
SDL_COMPILE_FLAGS=`sdl-config --prefix=/projects/local/work --cflags`
SDL_LINK_FLAGS=`sdl-config --prefix=/projects/local/work --libs`

COMPILE_COMMAND=g++ ${SDL_COMPILE_FLAGS} ${BOOST_COMPILE_FLAGS} ${CPPFLAGS} -Wall -ansi -Werror
LINK_COMMAND=g++ ${SDL_LINK_FLAGS} ${BOOST_LINK_FLAGS} ${LDFLAGS} -lm -lstdc++


all: build sdlpp link

link:
	${LINK_COMMAND} *.o SDL/*.o -o raytrace

build:
	${COMPILE_COMMAND} *.cpp -c

sdlpp:
	cd SDL; make ${MFLAGS} -f ../Makefile sdlppi; cd ..

sdlppi: CDRom.cpp Cursor.cpp Event.cpp Init.cpp Overlay.cpp Surface.cpp Timer.cpp Window.cpp
	${COMPILE_COMMAND} *.cpp -c	

CDRom.cpp:
	${COMPILE_COMMAND} CDRom.cpp -c

Cursor.cpp:
	${COMPILE_COMMAND} Cursor.cpp -c

Event.cpp:
	${COMPILE_COMMAND} Event.cpp -c

Init.cpp:
	${COMPILE_COMMAND} Init.cpp -c

Overlay.cpp:
	${COMPILE_COMMAND} Overlay.cpp -c

Surface.cpp:
	${COMPILE_COMMAND} Surface.cpp -c

Timer.cpp:
	${COMPILE_COMMAND} Timer.cpp -c

Window.cpp:
	${COMPILE_COMMAND} Window.cpp -c

clean:
	-rm -rf *.o SDL/*.o core raytrace

