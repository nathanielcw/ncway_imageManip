#include "../incl/matrix.h"

Matrix::Matrix( int x, int y )
{
	this->_x = x;
	this->_y = y;
	this->_data = (double*)malloc( x*y*(sizeof( double ) ) );
}

Matrix::Matrix( int x, int y, double* in )
{	
	this->_x = x;
	this->_y = y;
	this->_data = (double*)malloc( x*y*(sizeof( double ) ) );
	this->populate( in );
}

void Matrix::x( int s )
{
	this->_x = s;
}

void Matrix::y( int s )
{
	this->_y = s;
}

int Matrix::x()
{
	return this->_x;
}

int Matrix::y()
{
	return this->_y;
}

double Matrix::value( int x, int y )
{
	if( x < this->x() && y < this->y() ){
		return this->_data[ ( y * this->x() ) + x ];
	}else{
		printf( "\n matrix position outside of dimensions\n" );
	}
	return -0.0;
}	

void Matrix::populate( double* input )
{
	for( int i = 0; i < this->x() * this->y(); ++i ){ 
		this->_data[i] = input[i];
	}
} 

//populate specific position in matrix by x,y address
void Matrix::poppos( int x, int y, double in )
{
	this->_data[ (y*this->x() ) + x ] = in;
}

//multiply two matrices and return pointer to a dynamically allocated product matrix
Matrix* MMult( Matrix* A, Matrix* B )
{
	assert( A->x() == B->y() );

	Matrix* out = new Matrix( B->x(), A->y() );
	double buff;
	for(int ar = 0; ar < A->y(); ++ar  ){//each y of A
		for( int bc = 0; bc  < B->x(); ++bc ){//each x in B
			//for the given row in A and column in B
			buff = 0.0;
			for( int i = 0; i < A->x(); ++i ){//
				buff = buff + ( A->value( i, ar ) * B->value( bc, i ) );
			}
			out->poppos( bc, ar, buff );
		}
	}
	return out;
}

//add two matrices
Matrix* MAdd( Matrix* A, Matrix* B )
{
	assert( A->x() == B->x() && A->y() == B->y() );
	Matrix* out = new Matrix( A->x(), A->y() );
	for( int r = 0; r < A->y(); ++r ){
		for( int c = 0; c < A->x(); ++c ){
			out->poppos( c, r, 
					(double)(A->value( c, r ) + B->value( c, r ) ) );
		}
	}
	return out;
}
