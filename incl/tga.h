#ifndef TGA24_H
#define TGA24_H

#include <stdio.h>
#include <cstdlib>
#include <stdint.h>
#include "../incl/const.h"
using namespace std;

class Tga24
{
	public:
	int height();
	int width();
	int r( int x, int y );
	int b( int x, int y );
	int g( int x, int y );
	
	protected:
	int _height;
	int _width;
	int*  _pic;
	FILE* _image;


		
};

#endif

#ifndef TGA24R_H
#define TGA24R_H

using namespace std;

class Tga24r: public Tga24
{	
	public:
	Tga24r( char* filename );
	~Tga24r();
	int* data();
	
};

#endif

#ifndef TGA24W_H
#define TGA24W_H

using namespace std;
class Tga24w: public Tga24
{
	public:
	Tga24w( char* filename, int h, int w );
	~Tga24w();
	void copy( int* d );
	int pos( int x, int y, int color );
	int pos( int x, int y, int r, int b, int g );
	int red( int x, int y, int r );
	int blue( int x, int y, int b );
	int green( int x, int y, int g );
};

#endif
