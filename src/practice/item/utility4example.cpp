#include "utility4example.hpp"

#include <cstdio>
#include <cstdlib>

namespace u4e
{
	int randomi( const int min_value, const int max_value )
	{
		int rnd = 0;

		while( ( rnd = rand() ) == RAND_MAX );

		return min_value + ( int )( ( double )rnd / RAND_MAX * ( max_value - min_value + 1 ) );
	}
	void test_randomi()
	{
		for( int i = 0; 100 > i; ++i )
		{
			printf( "%d\n", randomi( 1, 5 ) );
		}
	}

	float randomf( const float min_value, const float max_value )
	{
		return min_value + ( ( float )rand() / RAND_MAX * ( max_value - min_value ) );
	}
	void test_randomf()
	{
		for( int i = 0; 100 > i; ++i )
		{
			printf( "%f\n", randomf( 1, 5 ) );
		}
	}
}