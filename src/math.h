#ifndef MATH_H
#define MATH_H



//matrix and vector functions
void Mat4Identity( float* m );

void Vec3Mat4Mul( const float* v, const float* m, float* v_dst );
void Vec3Mat4Mul( float* v_dst, const float* m );

void Mat4Mul( const float* m1, const float* m2, float* m_dst );
void Mat4Mul( float* m1_dst, const float* m2 );


#define MRPG_PI 3.1451926535f

/*
if target is win32 and compiler is M$ Visual Studio default math functions from math.h replaced by inlined asm functions.
*/

#ifndef MRPG_IA32_MASM
#include <math.h>
#endif


#ifdef MRPG_IA32_MASM

inline void cos( float a )
{
    float r;
    __asm
    {
        fld x
        fcos
        fstp r
    }
    return r;
}

inline void sin( float a )
{
    float r;
    __asm
    {
        fld x
        fsin
        fstp r
    }
    return r;
}


float tan( float x )
{
    float r;
    __asm
    {
        fld x
        fptan
        fstp r
        fstp r
    }
    return r;
}

float fabs( float x )
{
    float r;
    __asm
    {
        fld x
        fabs
        fstp r
    }
    return r;
}

#endif//MRPG_IA32_MASM

#endif//MATH_H
