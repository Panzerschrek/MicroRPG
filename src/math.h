#ifndef MATH_H
#define MATH_H

void Mat4Identity( float* m );
void Vec3Mat4Mul( const float* v, const float* m, float* v_dst );
void Mat4Mul( const float* m1, const float* m2, float* m_dst );
#endif//MATH_H
