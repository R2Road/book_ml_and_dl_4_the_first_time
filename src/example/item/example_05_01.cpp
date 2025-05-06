#include "example_05_01.hpp"

#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <math.h> // exp

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "utility4example.hpp"

namespace example_05_01
{
	const int INPUTSIZE = 11;	// 입력 수
	const int FILTERSIZE = 3;	// 필터 크기
	const int POOLSIZE = 3;		// 풀링 크기
	const int POOLOUTSIZE = 3;	// 풀링 출력 크기

	// 합성곱 결과 출력
	void print_conv( double convout[][INPUTSIZE] )
	{
		for( int i = 0; INPUTSIZE > i; ++i )
		{
			printf( "    " );
			for( int j = 0; INPUTSIZE + 1 > j; ++j )
			{
				printf( "%.3lf  ", convout[i][j] );
			}
			printf( "\n" );
		}
	}
	// 합성곱 계산
	void conv(
		  double filter[][FILTERSIZE]
		, double e[][INPUTSIZE]
		, double convout[][INPUTSIZE]
	)
	{
		filter;
		e;
		convout;
	}
	// 필터 적용
	double calcconv(
		  double filter[][FILTERSIZE]
		, double e[][INPUTSIZE]
		, int i
		, int j
	)
	{
		filter;
		e;
		i;
		j;

		return 0;
	}


	// 풀링 결과 출력
	void print_pool( double poolout[][POOLOUTSIZE] )
	{
		for( int i = 0; POOLOUTSIZE > i; ++i )
		{
			printf( "    " );
			for( int j = 0; POOLOUTSIZE + 1 > j; ++j )
			{
				printf( "%.3lf  ", poolout[i][j] );
			}
			printf( "\n" );
		}
	}
	// 최댓값 풀링
	double maxpooling(
		  double convout[][INPUTSIZE]
		, int i
		, int j
	)
	{
		const int halfpool = POOLSIZE / 2;	// 풀링 크기의 1/2

		// 최댓값
		double max = convout[i * POOLOUTSIZE + 1 + halfpool][j * POOLOUTSIZE + 1 + halfpool];

		for( int m = POOLOUTSIZE * i + 1; POOLOUTSIZE * i + 1 + ( POOLSIZE - halfpool ) >= m; ++m )
		{
			for( int n = POOLOUTSIZE * j + 1; POOLOUTSIZE * j + 1 + ( POOLSIZE - halfpool ) >= n; ++n )
			{
				if( max < convout[m][n] )
				{
					max = convout[m][n];
				}
			}
		}

		return max;
	}
	// 풀링 계산
	void pool(
		  double convout[][INPUTSIZE]
		, double poolout[][POOLOUTSIZE]
	)
	{
		for( int i = 0; POOLOUTSIZE > i; ++i )
		{
			for( int j = 0; POOLOUTSIZE > j; ++j )
			{
				poolout[i][j] = maxpooling( convout, i, j );
			}
		}
	}
	



	// 데이터 읽어들이기
	int load_input( double e[][INPUTSIZE] )
	{
		int n_of_e = 0; // 데이터 집합 개수

		FILE* fp = nullptr;
		if( 0 != fopen_s( &fp, "resources/chapter_05_01.txt", "rb" ) )
		{
			return 0;
		}

		// 꼭 코드를 이렇게 만들어야 하는 걸까?
		int i = 0;
		while( EOF != fscanf_s( fp, "%lf", &e[n_of_e][i] ) )
		{
			++i;
			if( INPUTSIZE <= i )
			{
				i = 0;
				++n_of_e;
			}
		}

		return n_of_e;
	}
	void print_input( const int count, double e[][INPUTSIZE] )
	{
		printf( "# Data List\n" );
		for( int i = 0; count > i; ++i )
		{
			printf( "    " );
			for( int j = 0; INPUTSIZE > j; ++j )
			{
				printf( "%.3lf   ", e[i][j] );
			}
			printf( "\n" );
		}
	}




	r2tm::TitleFunctionT LoadInputData::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "example : 5 - 1 : Load Input Data";
		};
	}
	r2tm::DoFunctionT LoadInputData::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			OUTPUT_NOTE( "데이터 읽기" );

			LS();

			DECLARATION_MAIN( double e[INPUTSIZE][INPUTSIZE] ); // 데이터 집합

			LF();

			DECLARATION_MAIN( const int n_of_e = load_input( e ) );
			OUTPUT_VALUE( n_of_e );

			LF();

			PROCESS_MAIN( print_input( n_of_e, e ) );

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Do::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "example : 5 - 1 : Do";
		};
	}
	r2tm::DoFunctionT Do::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			

			LS();

			{
				
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}