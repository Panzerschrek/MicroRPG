float Noise2(const int x, const int y)   //range - [-1;1]
{
    int n = x + y * 57;
    n = (n << 13) ^ n;
    return ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) /
    1073741823.5f - 1.0f;
}

float InterpolatedNoise(const short x, const short y)   //range - [-1;1]
{
    const short X = x >> 6;
    const short Y = y >> 6;

    const float noise[4]=
    {
        Noise2(X, Y),
        Noise2(X + 1, Y),
        Noise2(X + 1, Y + 1),
        Noise2(X, Y + 1)
    };

    const float dx = (float (x) - float (X << 6))*0.015625f;
    const float dy = (float (y) - float (Y << 6))*0.015625f;

    const float interp_x[2]=
    {
        dy * noise[3] + (1.0f - dy) * noise[0],
        dy * noise[2] + (1.0f - dy) * noise[1]
    };
    return interp_x[1] * dx + interp_x[0] * (1.0f - dx);
}

float FinalNoise(short x, short y)   //range [-1;1]  middle= 0
{
    float r = 0.5f * InterpolatedNoise(x, y);

    x <<= 1, y <<= 1;
    r += 0.25f * InterpolatedNoise(x, y);


    x <<= 1, y <<= 1;
    return (r += 0.125f * InterpolatedNoise(x, y));
}


unsigned char* GenBackground( unsigned int size_x, unsigned int size_y )
{
	unsigned char s;
	unsigned char* data= new unsigned char[ size_x* size_y ];
	unsigned int i, j;
	for( i= 0; i< size_x; i++ )
		for( j= 0; j< size_y; j++ )
		{
			s= (unsigned char) ((FinalNoise( i, j ) + 1.0f ) * 0.5f * 255.0f );
			data[i + j * size_x ]= ( s> 110 )? 255: 100;
		}

	return data;

}
