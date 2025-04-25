#include "example_04_01.hpp"

#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <math.h> // exp

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "utility4example.hpp"

namespace example_04_01
{
	const int INPUTNO = 2;			// 입력 갯수
	const int MAXINPUTNO = 100;		// 데이터의 최대 개수



	// 가중치와 문턱값 초기화
	void init_w( double w[INPUTNO + 1] )
	{
		// 가중치
		w[0] = 1;
		w[1] = 1;

		// 문턱값
		w[2] = 1.5;
		// w[2] = 0.5;
	}
	void print_w( double w[INPUTNO + 1] )
	{
		for( int i = 0; INPUTNO + 1 > i; ++i )
		{
			printf( "%.2f  ", w[i] );
		}
		printf( "\n" );
	}

	// 데이터 읽기
	int getdata( double e[][INPUTNO] )
	{
		int n_of_e = 0; // 데이터 집합 개수

		FILE* fp = nullptr;
		if( 0 != fopen_s( &fp, "resources/chapter_04_01.txt", "rb" ) )
		{
			return false;
		}

		// 꼭 코드를 이렇게 만들어야 하는 걸까?
		int i = 0;
		while( EOF != fscanf_s( fp, "%lf", &e[n_of_e][i] ) )
		{
			++i;
			if( INPUTNO <= i )
			{
				i = 0;
				++n_of_e;
			}
		}

		return n_of_e;
	}
	void print_data( const int count, double e[][INPUTNO] )
	{
		printf( "# Data List\n" );
		for( int i = 0; count > i; ++i )
		{
			printf( "    %.3f   %.2f\n", e[i][0], e[i][1] );
		}
	}



	// 전달 함수( 활성함수 라고도 하는듯. Activation Function )
	double f( double u )
	{
		// 계단 함수
		if( 0 <= u )
		{
			return 1.0;
		}
		else
		{
			return 0.0;
		}

		// 시그모이드 함수
		//
		// exp
		// - 자연 상수 e를 제곱한 결과를 반환하는 함수
		// - e^arg
		//return 1.0 / ( 1.0 + exp( -u ) ) ; // 시그모이드 함수 그대로의 표현
	}
	// 순방향 계산
	double forward( double w[INPUTNO + 1], double e[INPUTNO] )
	{
		int i = 0;
		double u = 0; // 중간 계산값
		double o = 0; // 출력값

		//
		// 계산
		// 
		
		// 1 단계
		// - 각각의 입력에 가중치를 곱한다.
		// - 그 결과를 모두 더한다.
		//
		for( i = 0; INPUTNO > i; ++i )
		{
			u += e[i] * w[i];
		}

		// 2 단계
		// - 문턱값 처리
		// 
		// 꼭 코드를 이 따위로 작성해야 하나? 흠.
		u -= w[i];

		// 3 단계
		// - 전달 함수 처리
		o = f( u );

		return o;
	}



	r2tm::TitleFunctionT LoadData::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "example : 4 - 1 : Load Data";
		};
	}
	r2tm::DoFunctionT LoadData::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			OUTPUT_NOTE( "데이터 읽기" );

			LS();

			DECLARATION_MAIN( double e[MAXINPUTNO][INPUTNO] ); // 데이터 집합

			LF();

			DECLARATION_MAIN( const int n_of_e = getdata( e ) );
			OUTPUT_VALUE( n_of_e );

			LF();

			PROCESS_MAIN( print_data( n_of_e, e ) );

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Do::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "example : 4 - 1 : Do";
		};
	}
	r2tm::DoFunctionT Do::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			OUTPUT_NOTE( "하나의 인공 신경 계산" );
			OUTPUT_NOTE( "적당한 가중치와 문턱값을 가진 인공 신경을 흉내 냄" );

			LF();

			OUTPUT_SUBJECT( "작업 절차" );
			OUTPUT_COMMENT( "가중치, 문턱값 초기화" );
			OUTPUT_COMMENT( "입력 데이터 읽기" );
			OUTPUT_COMMENT( "계산" );
			OUTPUT_COMMENT( "   1. 입력값 과 가중치를 곱하여 모두 더함" );
			OUTPUT_COMMENT( "   2. 문턱값 뺌" );
			OUTPUT_COMMENT( "   3. 전달 함수를 이용하여 출력값 계산" );

			LS();

			{
				DECLARATION_MAIN( double e[MAXINPUTNO][INPUTNO] );		// 데이터 집합
				DECLARATION_MAIN( const int n_of_e = getdata( e ) );	// 데이터 읽기
				OUTPUT_VALUE( n_of_e );

				LF();

				DECLARATION_MAIN( double w[INPUTNO + 1] );				// 가중치와 문턱값
				PROCESS_MAIN( init_w( w ) );							// 가중치 초기화
				PROCESS_MAIN( print_w( w ) );

				LF();

				DECLARATION_MAIN( double o = 0 );						// 출력

				SS();

				// 계산 본체
				{
					for( int i = 0; n_of_e > i; ++i )
					{
						printf( "%2d", i );

						printf( "      input : " );
						for( int j = 0; INPUTNO > j; ++j )
						{
							printf( "%.2lf ", e[i][j] );
						}

						o = forward( w, e[i] );
						printf( "      output : %.2lf\n", o );
					}
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}