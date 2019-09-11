gxx=g++
arma=-larmadillo
opts= -std=c++11 -march=native -O3

all: core.o triangles.o sdl_core.o

core.o: core.cpp
	${gxx} -c -o $@ $? ${arma} ${opts} 

triangles.o: triangles.cpp core.o
	${gxx} -c -o $@ triangles.cpp ${arma} ${opts} 

sdl_core.o: sdl_core.cpp sdl_core.h core.o
	${gxx} -c -o $@ sdl_core.cpp ${arma} ${opts} 

clean: *.o
	rm *.o
