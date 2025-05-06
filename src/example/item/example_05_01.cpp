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

	// 필터 출력
	void print_filter( const double filter[FILTERSIZE][FILTERSIZE] )
	{
		for( int i = 0; FILTERSIZE > i; ++i )
		{
			printf( "    " );
			for( int j = 0; FILTERSIZE > j; ++j )
			{
				printf( "%.3lf  ", filter[i][j] );
			}
			printf( "\n" );
		}
	}
	void make_filter( const int type, const double filter[FILTERSIZE][FILTERSIZE] )
	{
		static const double f1[FILTERSIZE][FILTERSIZE] = { { 0, 0, 0 }, { 1, 1, 1 }, { 0, 0, 0 } }; // 가로 필터
		static const double f2[FILTERSIZE][FILTERSIZE] = { { 0, 1, 0 }, { 0, 1, 0 }, { 0, 1, 0 } }; // 세로 필터

		switch( type )
		{
		case 'w': // 가로
			memcpy_s( (void*)filter, sizeof( double ) * FILTERSIZE * FILTERSIZE, f1, sizeof( double ) * FILTERSIZE * FILTERSIZE );
			break;
		case 'q': // 세로
		case 'e': // 대각선
			memcpy_s( ( void* )filter, sizeof( double ) * FILTERSIZE * FILTERSIZE, f2, sizeof( double ) * FILTERSIZE * FILTERSIZE );
			break;
		}
	}



	// 합성곱 결과 출력
	void print_conv( double convout[][INPUTSIZE] )
	{
		for( int i = 1; INPUTSIZE - 1 > i; ++i )
		{
			printf( "    " );
			for( int j = 1; INPUTSIZE - 1 > j; ++j )
			{
				printf( "%.3lf  ", convout[i][j] );
			}
			printf( "\n" );
		}
	}
	// 필터 적용
	double calcconv(
		  const double filter[][FILTERSIZE]
		, double e[][INPUTSIZE]
		, int i
		, int j
	)
	{
		double sum = 0;	// 합계값

		for( int m = 0; FILTERSIZE > m; ++m )
		{
			for( int n = 0; FILTERSIZE > n; ++n )
			{
				sum += e[i - FILTERSIZE / 2 + m][j - FILTERSIZE / 2 + n] * filter[m][n];
			}
		}

		return sum;
	}
	// 합성곱 계산
	void conv(
		  const double filter[][FILTERSIZE]
		, double e[][INPUTSIZE]
		, double convout[][INPUTSIZE]
	)
	{
		// 합성곱 범위의 하한
		const int startpoint = FILTERSIZE / 2;

		for( int i = startpoint; INPUTSIZE - startpoint > i; ++i )
		{
			for( int j = startpoint; INPUTSIZE - startpoint > j; ++j )
			{
				convout[i][j] = calcconv( filter, e, i, j );
			}
		}
	}
	


	// 풀링 결과 출력
	void print_pool( double poolout[][POOLOUTSIZE] )
	{
		for( int i = 0; POOLOUTSIZE > i; ++i )
		{
			printf( "    " );
			for( int j = 0; POOLOUTSIZE > j; ++j )
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
	int load_input( const int type, double e[][INPUTSIZE] )
	{
		int n_of_e = 0; // 데이터 집합 개수

		const char* file_path = nullptr;
		switch( type )
		{
		case 'q': // 세로
			file_path = "resources/chapter_05_01_01.txt";
			break;
		case 'w': // 가로
			file_path = "resources/chapter_05_01_02.txt";
			break;
		case 'e': // 대각선
			file_path = "resources/chapter_05_01_03.txt";
			break;
		}

		FILE* fp = nullptr;
		if( 0 != fopen_s( &fp, file_path, "rb" ) )
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

			DECLARATION_MAIN( int n_of_e );
			DECLARATION_MAIN( double e[INPUTSIZE][INPUTSIZE] ); // 데이터 집합

			SS();

			PROCESS_MAIN( n_of_e = load_input( 'q', e ) );
			OUTPUT_VALUE( n_of_e );
			PROCESS_MAIN( print_input( n_of_e, e ) );

			SS();

			PROCESS_MAIN( n_of_e = load_input( 'w', e ) );
			OUTPUT_VALUE( n_of_e );
			PROCESS_MAIN( print_input( n_of_e, e ) );

			SS();

			PROCESS_MAIN( n_of_e = load_input( 'e', e ) );
			OUTPUT_VALUE( n_of_e );
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

			OUTPUT_NOTE( "합성곱과 풀링 처리" );
			OUTPUT_NOTE( "2차원 데이터를 읽어들여 합성곱과 풀링을 실시" );

			LF();

			OUTPUT_SUBJECT( "작업 절차" );
			OUTPUT_COMMENT( "합성곱을 수행하는 필터 초기화" );
			OUTPUT_COMMENT( "합성곱 계산" );
			OUTPUT_COMMENT( "   다음을 입력 데이터 전체 영역에 대해 반복" );
			OUTPUT_COMMENT( "   1. 필터의 각 점을 입력 데이터의 대응점에 겹쳐 화소마나 누적합을 계산" );
			OUTPUT_COMMENT( "   2. 앞에서 구한 값을 집어 넣어 출력 데이터에 추가" );
			OUTPUT_COMMENT( "풀링 계산" );
			OUTPUT_COMMENT( "결과 출력" );

			LS();

			OUTPUT_SUBJECT( "작동 데이터 선택" );
			OUTPUT_COMMENT( "Q. 세로" );
			OUTPUT_COMMENT( "W. 가로" );
			OUTPUT_COMMENT( "E. 대각선" );
			int type = 0;
			while( !( 'q' == type || 'w' == type || 'e' == type ) )
			{
				type = _getch();
			}

			LS();

			{
				DECLARATION_MAIN( double filter[FILTERSIZE][FILTERSIZE] );
				PROCESS_MAIN( make_filter( type, filter ) );
				PROCESS_MAIN( print_filter( filter ) );

				LF();

				DECLARATION_MAIN( double e[INPUTSIZE][INPUTSIZE] ); // 데이터 집합
				DECLARATION_MAIN( const int n_of_e = load_input( type, e ) );
				OUTPUT_VALUE( n_of_e );
				PROCESS_MAIN( print_input( n_of_e, e ) );

				LF();

				double convout[INPUTSIZE][INPUTSIZE] = { 0 };	// 합성곱 출력
				double poolout[POOLOUTSIZE][POOLOUTSIZE];		// 출력 데이터

				LF();

				// 합성곱 계산
				PROCESS_MAIN( conv( filter, e, convout ) );
				PROCESS_MAIN( print_conv( convout ) );
				
				LF();

				// 풀링 계산
				PROCESS_MAIN( pool( convout, poolout ) );

				LF();

				// 결과 출력
				PROCESS_MAIN( print_pool( poolout ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}