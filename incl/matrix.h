#ifndef MATRIX_H
#define MATRIX_H
#include <cstdlib>
#include <stdio.h>
#include <cassert>

using namespace std;

class Matrix
{
	
	public:
	Matrix( int x, int y, double* in );
	Matrix( int x, int y );
	int x();
	int y();
	void x( int );
	void y( int );
	double value( int x, int y );
	void populate( double* input );
	void poppos( int x, int y, double );
	private:
	int _x;
	int _y;
	double* _data;

};

#endif

#ifndef MOP_H
#define MOP_H

using namespace std;

Matrix* MMult( Matrix* a, Matrix* b );

Matrix* MAdd( Matrix* a, Matrix* b );

#endif

