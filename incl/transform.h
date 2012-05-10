#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "../incl/matrix.h"
#include "../incl/tga.h"
#include <cmath>

using namespace std;

void negative( Tga24w* out );
void bw( Tga24w* out, int r, int b, int g );
void resize( Tga24r* in, Tga24w* out,  int per );
void dither( Tga24w* out,  int thoffset, int cont );
void contrast( Tga24w* out, int cont );
void contrastUp( Tga24w* );
void contrastDown( Tga24w* );
void brightness( Tga24w* out, int bright );
void trim( Tga24w* out );
void box( Tga24w* out );
void gauss( Tga24w* out );
void sharp( Tga24w* out );
void smear( Tga24w* out );

#endif
