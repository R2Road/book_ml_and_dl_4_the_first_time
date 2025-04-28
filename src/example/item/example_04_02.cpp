#include "example_04_02.hpp"

#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <math.h> // exp

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "utility4example.hpp"

namespace example_04_02
{
	const int INPUTNO = 2;			// 입력 갯수
	const int HIDDENNO = 2;			// 중간층의 셀 개수
	const int MAXINPUTNO = 100;		// 데이터의 최대 개수



	// 중간층의 가중치와 초기화
	void init_wh( double wh[HIDDENNO][INPUTNO + 1] )
	{
		wh[0][0] = -2;
		wh[0][1] = 3;
		wh[0][2] = -1;
		wh[1][0] = -2;
		wh[1][1] = 1;
		wh[1][2] = 0.5;
		
	}
	void print_wh( double wh[HIDDENNO][INPUTNO + 1] )
	{
		for( int i = 0; HIDDENNO > i; ++i )
		{
			printf( "    " );
			for( int j = 0; INPUTNO + 1 > j; ++j )
			{
				printf( "%.2f  ", wh[i][j] );
			}
			printf( "\n" );
		}
	}

	// 출력층의 가중치와 초기화
	void init_wo( double wo[HIDDENNO + 1] )
	{
		wo[0] = -60;
		wo[1] = 94;
		wo[2] = -1;
	}
	void print_wo( double wo[HIDDENNO + 1] )
	{
		printf( "    " );
		for( int i = 0; HIDDENNO + 1 > i; ++i )
		{
			printf( "%.2f  ", wo[i] );
		}
		printf( "\n" );
	}

	// 데이터 읽기
	int load_input( double e[][INPUTNO] )
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
	void print_input( const int count, double e[][INPUTNO] )
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
	double forward(
		  double wh[HIDDENNO][INPUTNO + 1]
		, double wo[HIDDENNO + 1]
		, double hi[]
		, double e[INPUTNO]
	)
	{
		double u = 0; // 중간층 계산값
		double o = 0; // 출력층 계산값

		//
		// 중간층 계산
		// 
		int i = 0;
		int j = 0;
		for( i = 0; HIDDENNO > i; ++i )
		{
			u = 0;
			for( j = 0; INPUTNO > j; ++j )
			{
				// 1 단계
				// - 각각의 입력에 가중치를 곱한다.
				// - 그 결과를 모두 더한다.
				u += e[j] * wh[i][j];
			}

			// 2 단계
			// - 문턱값 처리
			//
			// 알아보기 힘들게 이따위로 코드를 짜야 하나?
			u -= wh[i][j];

			// 3 단계
			// - 중간층 출력 값 저장
			hi[i] = f( u );
		}

		//
		// 출력층 계산
		//
		o = 0;
		for( i = 0; HIDDENNO > i; ++i )
		{
			// 1 단계
			// - 각각의 입력에 가중치를 곱한다.
			// - 그 결과를 모두 더한다.
			o += hi[i] * wo[i];
		}
		// 2 단계
		// - 문턱값 처리
		//
		// 알아보기 힘들게 이따위로 코드를 짜야 하나?
		o -= wo[i];

		return f( o );
	}



	r2tm::TitleFunctionT LoadInputData::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "example : 4 - 2 : Load Input Data";
		};
	}
	r2tm::DoFunctionT LoadInputData::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			OUTPUT_NOTE( "데이터 읽기" );

			LS();

			DECLARATION_MAIN( double e[MAXINPUTNO][INPUTNO] ); // 데이터 집합

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
			return "example : 4 - 2 : Do";
		};
	}
	r2tm::DoFunctionT Do::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			OUTPUT_NOTE( "단순한 계층형 신경망 계산" );
			OUTPUT_NOTE( "출력망을 계산( 학습 없음 )" );

			LF();

			OUTPUT_SUBJECT( "신경망 구조" );
			OUTPUT_COMMENT( "2개의 입력 -> 2개의 중간층 -> 1개의 출력층" );

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
				DECLARATION_MAIN( const int n_of_e = load_input( e ) );	// 데이터 읽기
				OUTPUT_VALUE( n_of_e );
				PROCESS_MAIN( print_input( n_of_e, e ) );

				LF();

				DECLARATION_MAIN( double wh[HIDDENNO][INPUTNO + 1] );	// 중간층 가중치와 문턱값
				PROCESS_MAIN( init_wh( wh ) );							// 가중치 초기화
				PROCESS_MAIN( print_wh( wh ) );

				LF();

				DECLARATION_MAIN( double wo[INPUTNO + 1] );				// 출력층 가중치와 문턱값
				PROCESS_MAIN( init_wo( wo ) );							// 가중치 초기화
				PROCESS_MAIN( print_wo( wo ) );

				LF();

				DECLARATION_MAIN( double hi[INPUTNO + 1] );				// 중간층 출력
				DECLARATION_MAIN( double o = 0 );						// 출력층 출력

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

						o = forward( wh, wo, hi, e[i] );
						printf( "      output : %.2lf\n", o );
					}
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}