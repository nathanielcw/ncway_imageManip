#include "../incl/matrix.h"
#include <stdio.h>

using namespace std;

void showMatrix( Matrix* );

int main( int argc, char** argv )
{
	double info1[12] = {  	0.1, 1.2, 2.3, 3.4,
			   	4.5, 5.6, 7.8, 9.0,
				1.3, 1.537, 0.5, 1.0 };
	
	double info2[20] = { 	1.0, 2.0, 3.0, 4.0,
                                5.0, 6.0, 7.0, 8.0,
                                9.0, 1.5, 2.5, 3.5,
				4.5, 5.5, 6.5, 7.5,
				8.5, 9.5, 10, 10.5  };

	Matrix* A = new Matrix( 3, 4, info2 );
	Matrix* B = new Matrix( 4, 3, info2 );
	Matrix* C = MMult( A, B );

	showMatrix( A );
	showMatrix( B );
	showMatrix( C );
}

void showMatrix( Matrix* m )
{
	printf( "\n\nMatrix: %p \n", m );
	for( int r = 0; r < m->y(); ++r ){
		for( int c  = 0; c < m->x(); ++c ){
			if( c == 0 ){
				printf( "\n" );
			}
			printf( "%f ", m->value( c, r ) );
		}
	}

}
