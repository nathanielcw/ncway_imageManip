#include "../incl/transform.h"

void negative( Tga24w* out )
{
	for( int y = 0; y < out->height(); ++y ){ 
		for( int x = 0; x < out->width(); ++x ){
			out->blue( x, y, 255 - out->b( x, y ) );
			out->green( x, y, 255 - out->g( x, y ) );
			out->red( x, y, 255 - out->r( x, y ) );
		}
	}
}

void bw( Tga24w* out, int rlev, int glev, int blev )
{
	int buff = 0;
	for( int y = 0; y < out->height(); ++y ){ 
		for( int x = 0; x < out->width(); ++x ){
			buff= (( out->b(x,y)*blev)/1000 ) 
				+ ((out->g(x,y)*glev)/1000) 
				+ ((out->r(x,y)*rlev)/1000);
			out->blue( x, y, buff );
			out->green( x, y, buff );
			out->red( x, y, buff );
		}
	}
}
			
void resize( Tga24r* in, Tga24w* out, int per )
{

}

void dither( Tga24w* out, int thoffset, int noise )
{
	int bavg = 0;
	int ravg = 0;
	int gavg = 0;
	int p = 0;
	int brr = 0;
	int rrr = 0;
	int grr = 0;
	int d = noise;
	int cnt[3] = { 0,0,0 };
	//assume black and white
	for( int y = 0; y < out->height(); ++y ){
		for( int x = 0; x < out->width(); ++x ){
			if( out->g(x,y) < 255 && out->g(x,y) > 0 ){
				gavg = gavg + out->g(x,y);
				cnt[1]++;
			}
			if( out->r( x,y ) < 255 && out->r(x,y) > 0 ){
				ravg = ravg + out->r(x,y);
				cnt[0]++;
			}
			if( out->b( x, y ) < 255 && out->b(x,y) > 0 ){
				bavg = bavg + out->b(x,y);
				cnt[2]++;
			}
		}
	}
	gavg = gavg/cnt[1];
	ravg = ravg/cnt[0];
	bavg = bavg/cnt[2];
	printf( "\nrgb averages: %d, %d, %d \n", ravg,gavg,bavg ); 
	for( int y = 0; y < out->height(); ++y ){
		for( int x = 0; x < out->width(); ++x ){
			//zigzag, use p(x) rather than x for pixel x position
			p = x;
			if( y %2 ){
				p = out->width() - x;
			}
			brr = bavg-out->b( p, y );
			rrr = ravg-out->r( p, y );
			grr = gavg-out->g( p, y );
			if( y % 2 ){//right to left
				if( p > 0 ){
					out->blue( p-1, y, out->b( p-1, y ) + ( (700*brr)/d ));
					out->red( p-1, y, out->r( p-1, y ) + ( (700*rrr)/d ));
					out->green( p-1, y, out->g( p-1, y ) + ( (700*grr)/d ));
					if( y+1 < out->height() ){ 
						out->blue( p-1, y+1, out->b( p-1, y+1 ) + (100*brr/d));
						out->red( p-1, y+1, out->r( p-1, y+1 ) + (100*rrr/d));
						out->green( p-1, y+1, out->g( p-1, y+1 ) + (100*grr/d));
					}
				}
				if( y+1 < out->height() ){
					out->blue( p, y+1, out->b( p, y+1 ) + ((500*brr)/d));
					out->red( p, y+1, out->r( p, y+1 ) + ((500*rrr)/d));
					out->green( p, y+1, out->g( p, y+1 ) + ((500*grr)/d));
					if( p+1 < out->width() ){
						out->blue( p+1, y+1, out->b(p+1, y+1)+((300*brr)/d));
						out->red( p+1, y+1, out->r(p+1, y+1)+((300*rrr)/d));
						out->green( p+1, y+1, out->g(p+1, y+1)+((300*grr)/d));
					}
				}
			}else{//left to right
				if( p+1 < out->width() ){
					out->blue( p+1, y, out->b( p+1, y ) + ( (700*brr)/d ));
					out->red( p+1, y, out->r( p+1, y ) + ( (700*rrr)/d ));
					out->green( p+1, y, out->g( p+1, y ) + ( (700*grr)/d ));
					if( y+1 < out->height() ){ 
						out->blue( p+1, y+1, out->b( p+1, y+1 ) + (100*brr/d));
						out->red( p+1, y+1, out->r( p+1, y+1 ) + (100*rrr/d));
						out->green( p+1, y+1, out->g( p+1, y+1 ) + (100*grr/d));
					}
				}
				if( y+1 < out->height() ){
					out->blue( p, y+1, out->b( p, y+1 ) + ((500*brr)/d));
					out->red( p, y+1, out->r( p, y+1 ) + ((500*rrr)/d));
					out->green( p, y+1, out->g( p, y+1 ) + ((500*grr)/d));
					if( p-1 >= 0 ){
						out->blue( p-1, y+1, out->b(p-1, y+1)+((300*brr)/d));
						out->red( p-1, y+1, out->r(p-1, y+1)+((300*rrr)/d));
						out->green( p-1, y+1, out->g(p-1, y+1)+((300*grr)/d));
					}
				}
			}
			out->blue( p, y, 255 );
			out->red( p, y, 255 );
			out->green( p, y, 255 );
			if( brr + thoffset > 0 ){
				out->blue( p, y, 0 );
			}		
			if( rrr + thoffset > 0 ){
				out->red( p, y, 0 );
			}
			if( grr + thoffset > 0 ){
				out->green( p, y, 0 );
			}
		}
	}
}

void box( Tga24w* out )
{
        int br = 0;
	int bb = 0;
	int bg = 0;
	for( int y = 1; y < out->height()-1; ++y ){
		for( int x = 1; x < out->width()-1; ++x ){
			br = 0;
			bg = 0;
			bb = 0;
			for( int i = -1; i < 2; ++i ){
				for( int j = -1; j < 2; ++j ){
					br = br + out->r( j+x, i+y )/9;
					bg = bg + out->g( j+x, i+y )/9;
					bb = bb + out->b( j+x, i+y )/9;
				}
			}
			out->blue( x, y, bb );
			out->red( x, y, br );
			out->green( x, y, bg );
		}
	}
}

void contrast( Tga24w* out, int cont)
{
	for( int y = 0; y < out->height(); ++y ){
		for( int x = 0; x < out->width(); ++x ){
			out->blue( x,y, ( out->b( x, y) * cont )/100 );
			out->red( x,y, ( out->r( x, y) * cont )/100 );
			out->green( x,y, ( out->g( x, y) * cont )/100 );
		}
	}
}

void contrastDown( Tga24w* out )
{
	for( int y = 0; y < out->height(); ++y ){
		for( int x = 0; x < out->width(); ++x ){
			out->blue( x,y, ( out->b( x, y) * out->b( x, y ) )/255 );
			out->red( x,y, ( out->r( x, y) * out->r( x, y ) )/255 );
			out->green( x,y, ( out->g( x, y) * out->g( x, y ) )/255 );
		}
	}
}

void contrastUp( Tga24w* out )
{
	for( int y = 0; y < out->height(); ++y ){
		for( int x = 0; x < out->width(); ++x ){
			out->blue( x,y, ( (255-out->b( x, y)) * ( 255 - out->b( x, y )) )/(256*256) );
			out->red( x,y, ( out->r( x, y) * out->r( x, y ) )/(256*256) );
			out->green( x,y, ( out->g( x, y) * out->g( x, y ) )/(256*256)  );
		}
	}
}	

void brightness( Tga24w* out, int br )
{
	int b = (br*255)/100;
	for( int y = 0; y < out->height(); ++y ){
		for( int x = 0; x < out->width(); ++x ){
			out->blue( x,y, ( out->b( x, y) + b ));
			out->red( x,y, ( out->r( x, y) + b ));
			out->green( x,y, ( out->g( x, y) + b ));
		}
	}
}

void trim( Tga24w* out )
{
	for( int y = 0; y < out->height(); ++y ){
		for( int x = 0; x < out->width(); ++x ){
			if( out->b(x,y ) > 255 ){
				out->blue( x, y, 255 );
			}		
			if( out->r(x,y ) > 255 ){
				out->red( x, y, 255 );
			}
			if( out->g(x,y ) > 255 ){
				out->green( x, y, 255 );
			}
			if( out->b(x,y ) < 0 ){
				out->blue( x, y, 0 );
			}		
			if( out->r(x,y ) < 0 ){
				out->red( x, y, 0 );
			}
			if( out->g(x,y ) < 0 ){
				out->green( x, y, 0 );
			}
		}
	}
}
void gauss( char* infile, char* outfile )
{

}

void sharp( char* infile, char* outfile )
{

}

void smear( Tga24w* out )
{
	int br = 0;
	int bb = 0;
	int bg = 0;
	int div = 150;
	for( int y = 0; y < out->height(); ++y ){
		for( int x = 0; x < out->width(); ++x ){
			br = 0;
			bg = 0;
			bb = 0;
			for( int i = 150; i > 0; --i ){
				if(  i+x < out->width()){
					br = (br + out->r( i+x, y));
					bg = (bg + out->g( i+x, y));
					bb = (bb + out->b( i+x, y ));
				}
			}
			if( x+150 < out->width() ){
				div = 150;
			}else{
				div = out->width() - x;
			}
			out->blue( x, y, bb/div );
			out->red( x, y, br/div );
			out->green( x, y, bg/div );
		}
	}
}
