#include "../incl/tga.h"
#include <math.h>

using namespace std;

int main( int argc, char** argv )
{
	Tga24r* rTga = new Tga24r( "flower.tga" );
	Tga24w* wTga = new Tga24w( "rgbtest.tga", rTga->width(), rTga->height() );
	Tga24w* w2Tga = new Tga24w( "copytest.tga", rTga->width(), rTga->height() );
	for( int y = 0; y < rTga->height(); ++y ){
		for( int x = 0; x < rTga->width(); ++x ){
			wTga->blue( x, y, rTga->b( x, y ) );	
			wTga->green( x, y, rTga->g( x, y ) );
			wTga->red( x, y, rTga->r( x, y ) );
		}
	}
	w2Tga->copy( rTga->data() );
	
	delete rTga;
	delete wTga;
	delete w2Tga;
}
