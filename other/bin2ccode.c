#include <stdio.h>



int main( int argc, char* argv[] )
{
	char src_file_name[1024];
	char dst_file_name[1024];

	unsigned int src_file_len;
	unsigned int i, j;

	unsigned char* bin_data;
	int is_output_name= 0;

	for( i= 0; i< argc; i++ )
	{
		if( !strcmp( argv[i], "-o" ) )
		{
			if( i < argc - 1 )
			{
				strcpy( dst_file_name, argv[++i] );
				is_output_name= 1;
			}
			else
			{
				printf( "error, missing output file name before -o\n" );
				return 1;
			}
		}
		else
			strcpy( src_file_name, argv[i] );
	}
	if( argc == 0 )
	{
		printf( "error, no input file\n" );
		return 2;
	}

	if( ! is_output_name )
	{
		printf( "error, no output file name\n" );
		return 3;
	}

	FILE* f_src=fopen( src_file_name, "rb" );
	if( f_src == NULL )
	{
		printf( "file %s not found\n", src_file_name );
		return 4;
	}

	FILE* f_dst= fopen( dst_file_name, "wt" );	


	fseek( f_src, 0, SEEK_END ); 
	src_file_len= ftell( f_src );
	fseek( f_src, 0, SEEK_SET );

	bin_data= (unsigned char*) malloc( src_file_len );

	fread( bin_data, 1, src_file_len, f_src );
	fclose( f_src );


	fprintf( f_dst, "/*data from file \"%s\". Generated automatically*/\nunsigned char data[]= {\n", src_file_name );

	
		for( i= 0; i< src_file_len - 1; i++ )
		{
			fprintf( f_dst, " %d,", bin_data[i] );
			if( (i & 31) == 0 )
				fprintf( f_dst, "\n" );
		}
	
	fprintf( f_dst, " %d };", bin_data[ src_file_len - 1 ] );

	fclose( f_dst );
}
