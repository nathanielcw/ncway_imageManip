CC=g++
CFLAGS=-c -Wall -ggdb
LFLAGS=-o

clean:		all
	rm *.o
all:		weird
	./weird 75 12 1300
weird:		transform.o weird.o
	$(CC)  matrix.o tga.o transform.o weird.o $(LFLAGS) weird
weird.o:	transform.o src/weird.cpp
	$(CC) $(CFLAGS) src/weird.cpp
testM: 		matrix.o tmatrix.o
	$(CC) matrix.o tmatrix.o $(LFLAGS) matrixtest
testT:		ttga.o
	$(CC) ttga.o tga.o $(LFLAGS) tgatest
tmatrix.o:	matrix.o src/tmatrix.cpp
	$(CC) $(CFLAGS) src/tmatrix.cpp
transform.o:	src/transform.cpp incl/transform.h matrix.o tga.o
	$(CC) $(CFLAGS) src/transform.cpp
matrix.o: 	src/matrix.cpp incl/matrix.h
	$(CC) $(CFLAGS) src/matrix.cpp
ttga.o: 	tga.o src/ttga.cpp
	$(CC) $(CFLAGS) src/ttga.cpp
tga.o: 		incl/tga.h src/tga.cpp
	$(CC) $(CFLAGS) src/tga.cpp

