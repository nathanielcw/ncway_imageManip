#include "../incl/tga.h"

int Tga24::height()
{
	return this->_height;
}

int Tga24::width()
{
	return this->_width;
}

int Tga24::r( int x, int y )
{
	int ret;
	if( x < this->width() && y < this->height() ){
		ret = this->_pic[(((y * this->width() )+x)*3) + 2];
	}
	return ret;
}
       
int Tga24::b( int x, int y )
{
	int ret = -1;
	if( x < this->width() && y < this->height() ){
		ret = this->_pic[(((y * this->width() )+x)*3) ];
	}
	return ret;
}
     
int Tga24::g( int x, int y )
{	
	int ret = -1;
	if( x < this->width() && y < this->height() ){
		ret = this->_pic[(((y * this->width() )+x)*3) + 1 ];
	}
	return ret;
}

Tga24r::Tga24r( char* filename )
{
	//open the file, print success
	if( (this->_image = fopen( filename, "r" )) ){
		printf( "File %s opened successfully...", filename );
	}else{
		printf( "Problem opening file %s ... ", filename );
	}
	//write selected info from the header to this object
	//datatypecode 2
	fseek( this->_image, 2, SEEK_SET );
	if( fgetc( this->_image )  == 2 ){//check for expected value
		printf( "datatype code is 2..." );
	}else{
		printf( "datatypecode.. tga format unexpected\n" );
	}
	//width12&13
	fseek( this->_image, 12, SEEK_SET );
	this->_width = getc( this->_image );
	this->_width = this->_width + ( 256 * fgetc( this->_image ) );
	printf( "image width: %d \n", this->_width );
	//height14&15
	this->_height = fgetc( this->_image );
	this->_height = this->_height + ( 256 * fgetc( this->_image ) );
	printf( "image height: %d \n", this->_height );
	//bitsperpixel16
	if( fgetc( this->_image )  == 24 ){
		printf( " 24 bits per pixel \n" );
	}else{
		printf( "bits per pixel unexpected \n" );
	}
	if( fgetc( this->_image ) == 0 ){
		printf( "ok, now to write file to pixel data array " );
	}
        this->_pic = (int*)malloc( ( this->width() * this->height() 
					* 3 * sizeof( int ) ) + 1 );
        this->_pic[( this->width() * this->height() * 3 ) ] = 0;
	fseek( this->_image, 18, SEEK_SET );
	int s = this->height() * this->width() * 3;
	for( int i = 0; i < s; ++i ){
		this->_pic[i] = fgetc( this->_image );
	}
			 
}

Tga24r::~Tga24r()
{
	//free( this->_pic );
	//this->_pic = 0;
	fclose( this->_image );
}
 
int* Tga24r::data()
{
	return this->_pic;
}


Tga24w::Tga24w( char* filename, int w, int h )
{
	this->_height = h;
	this->_width = w;
	if( (this->_image = fopen( filename, "w" )) ){
		printf( "tga image %s opened", filename );
	}
	int header[18] = { 0,0,2,0,0,0,0,0,0,0,0,0,64,6,176,4,24,0 };
	for( int i = 0; i < 18; ++i ){
		fputc( header[i], this->_image );
	}
	fseek( this->_image, 12, SEEK_SET );
	fputc( w & 0x00FF, this->_image );
	fputc( ( w & 0xFF00 ) / 0x100, this->_image );
	fputc( h & 0x00FF, this->_image );
	fputc( ( h & 0xFF00 ) / 0x100, this->_image );
	fputc( 24, this->_image );
	fputc( 0, this->_image );
	int s = h*w*3;	
	this->_pic = (int*)malloc( ( s * sizeof( int )) + 1 );
        this->_pic[( this->width() * this->height() * 3 ) ] = 0;
	for( int i = 0; i < s; ++i ){
		this->_pic[ i ] = 0;
	}
}

Tga24w::~Tga24w()
{

	int size = this->height()*this->width()*3;
	fseek( this->_image, 18, SEEK_SET );
	for( int i = 0; i < size; ++i ){
		fputc( this->_pic[i], this->_image );
	}
	free( this->_pic );
	this->_pic = 0;
	printf( "\nsaved %d bytes\n ", size );
}

void Tga24w::copy( int* d ){
	int s = this->height() * this->width() * 3;
	for( int i = 0; i < s; ++i ){
		this->_pic[i] = d[i];
	}
}

int Tga24w::pos( int x, int y, int color )
{
	int ret = -1;
	if( x < this->width() && y < this->height() ){
		this->blue( x, y, 0x0000FF & color ); //blue first
		this->green( x, y, (0x00FF00 & color) / 0x100 ); //green
		this->red( x, y, (0xFF0000 & color) / 0x10000 ); //red
		ret = 0;
	}
	return ret;	
}

int Tga24w::pos( int x, int y, int r, int g, int b )
{
	int ret = -1;
	if( x < this->width() && y < this->height() ){
		this->blue( x, y, b ); //blue first
		this->green( x, y, g ); //green
		this->red( x, y, r ); //red
		ret = 0;
	}
	return ret;	
}      

int Tga24w::red( int x, int y, int r )
{
	int ret = -1;
	if( x < this->width() && y < this->height() ){
		this->_pic[(((y * this->width() )+x)*3)+2 ] = r;
		ret = 0;
	}
	return ret;
}
int Tga24w::blue( int x, int y, int b )
{
	int ret = -1;
	if( x < this->width() && y < this->height() ){
		this->_pic[(((y * this->width() )+x)*3) ] = b;
		ret = 0;
	}
	return ret;
}

int Tga24w::green( int x, int y, int g )
{
	int ret = -1;
	if( x < this->width() && y < this->height() ){
		this->_pic[(((y * this->width() )+x)*3)+1 ] = g;
		ret = 0;
	}
	return ret;
}
