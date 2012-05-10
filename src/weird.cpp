#include <stdio.h>
#include <cassert>
#include <cstdlib>
#include "../incl/transform.h"

using namespace std;

int main( int argc, char** argv )
{	
	Tga24r* in = new Tga24r( "flower.tga" );
	Tga24w* out = new Tga24w( "test.tga", in->width(), in->height() );
	out->copy( in->data() );
	negative( out );
	//brightness( out, atoi( argv[1] ) );
	//trim( out );
	bw( out, 299, 587, 114 ); 
	//contrastDown( out );
	contrastDown( out );
	//contrastDown( out );
	trim( out ); 
	negative( out );
	contrast( out, atoi( argv[1] ) );
	//brightness( out, atoi( argv[1] ) );
	trim( out );
	dither( out, atoi( argv[2] ), atoi(argv[3] ) );
	delete in;
	delete out;
}

