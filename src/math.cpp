
void Mat4Identity( float* m )
{
	unsigned int i= 0;
	for( i= 1; i< 15; i++ )
		m[i]= 0.0f;
	for( i= 0; i< 16; i+=5 )
		m[i]= 1.0f;
}


void Vec3Mat4Mul( const float* v, const float* m, float* v_dst )
{
	unsigned int i;
	for( i= 0; i< 3; i++ )
		v_dst[i]= v[0] * m[i] + v[1] * m[i+4] + v[2] * m[i+8] + m[i+12];
}


void Mat4Mul( const float* m1, const float* m2, float* m_dst )
{
	unsigned int i, j;

	for( i= 0; i< 4; i++ )
		for( j= 0; j< 16; j+=4 )
		{
			m_dst[ i + j ]= m1[ 0 + j ] * m2[ i ]   + 	 m1[ 1 + j ] * m2[ 4 + i ] +
							m1[ 2 + j ] * m2[ 8 + i ]   +  m1[ 3 + j ] * m2[ 12 + i ];
		}
}

