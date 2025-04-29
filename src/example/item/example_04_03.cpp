#include "example_04_03.hpp"

#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <math.h> // exp

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "utility4example.hpp"

namespace example_04_03
{
	const int INPUTNO = 3;			// 입력 갯수
	const int HIDDENNO = 3;			// 중간층의 셀 개수
	const int MAXINPUTNO = 100;		// 데이터의 최대 개수

	const double ALPHA = 10;		// 학습 계수
	const int RANDOM_SEED = 65535;	// 난수 시드

	const double BIGNUM = 100;		// 오차 초깃값
	const double LIMIT = 0.001;		// 오차 상한값



	// 중간층의 가중치와 초기화
	void init_wh( double wh[HIDDENNO][INPUTNO + 1] )
	{
		for( int i = 0; HIDDENNO > i; ++i )
		{
			for( int j = 0; INPUTNO + 1 > j; ++j )
			{
				wh[i][j] = u4e::randomf( -1.f, 1.f );
			}
		}
		
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
		for( int i = 0; HIDDENNO + 1 > i; ++i )
		{
			wo[i] = u4e::randomf( -1.f, 1.f );
		}
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
	int load_input( double e[][INPUTNO + 1] )
	{
		int n_of_e = 0; // 데이터 집합 개수

		FILE* fp = nullptr;
		if( 0 != fopen_s( &fp, "resources/chapter_04_03.txt", "rb" ) )
		{
			return false;
		}

		// 꼭 코드를 이렇게 만들어야 하는 걸까?
		int i = 0;
		while( EOF != fscanf_s( fp, "%lf", &e[n_of_e][i] ) )
		{
			++i;
			if( INPUTNO < i )
			{
				i = 0;
				++n_of_e;
			}
		}

		return n_of_e;
	}
	void print_input( const int count, double e[][INPUTNO + 1] )
	{
		printf( "# Data List\n" );
		for( int i = 0; count > i; ++i )
		{
			printf( "    %.3f   %.3f   %.3f   %.3f\n", e[i][0], e[i][1], e[i][2], e[i][3] );
		}
	}



	// 전달 함수( 활성함수 라고도 하는듯. Activation Function )
	double f( double u )
	{
		// 시그모이드 함수
		//
		// exp
		// - 자연 상수 e를 제곱한 결과를 반환하는 함수
		// - e^arg
		return 1.0 / ( 1.0 + exp( -u ) ) ; // 시그모이드 함수 그대로의 표현
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
	// 중간층 가중치 학습
	void hlearn(
		  double wh[HIDDENNO][INPUTNO + 1]
		, double wo[HIDDENNO + 1]
		, double hi[]
		, double e[INPUTNO + 1]
		, double o
	)
	{
		int i, j;
		double dj = 0; // 가중치 계산에 이용

		for( j = 0; HIDDENNO > j; ++j )
		{
			dj = hi[j] * ( 1 - hi[j] ) * wo[j] * ( e[INPUTNO] - o ) * o * ( 1 - o );

			// 가중치 학습
			for( i = 0; INPUTNO > i; ++i )
			{
				wh[j][i] += ALPHA * e[i] * dj;
			}

			// 문턱값 학습
			wh[j][i] += ( ALPHA * ( -1.0 ) * dj );
		}
	}
	// 출력층 가중치 학습
	void olearn(
		  double wo[HIDDENNO + 1]
		, double hi[]
		, double e[INPUTNO + 1]
		, double o
	)
	{
		int i = 0;		// 반복 제어
		double d = 0;	// 가중치 계산에 이용

		// 오차 계산
		d = ( e[INPUTNO] - o ) * o * ( 1 - o );

		// 가중치 학습
		for( i = 0; HIDDENNO > i; ++i )
		{
			wo[i] += ( ALPHA * hi[i] * d );
		}

		// 문턱값 학습
		wo[i] += ( ALPHA * ( -1.0 ) * d );
	}



	r2tm::TitleFunctionT LoadInputData::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "example : 4 - 3 : Load Input Data";
		};
	}
	r2tm::DoFunctionT LoadInputData::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			OUTPUT_NOTE( "데이터 읽기" );

			LS();

			DECLARATION_MAIN( double e[MAXINPUTNO][INPUTNO + 1] ); // 데이터 집합

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
			return "example : 4 - 3 : Do";
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

			LF();

			PROCESS_MAIN( srand( RANDOM_SEED ) );					// 난수 초기화

			LS();

			{
				DECLARATION_MAIN( double e[MAXINPUTNO][INPUTNO + 1] );		// 데이터 집합
				DECLARATION_MAIN( const int n_of_e = load_input( e ) );		// 데이터 읽기
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
				DECLARATION_MAIN( double err = BIGNUM );				// 오차 평가
				DECLARATION_MAIN( int count = 0 );						// 반복 횟수 카운터

				SS();

				// 학습
				while( LIMIT < err )
				{
					err = 0.0;

					for( int i = 0; n_of_e > i; ++i )
					{
						// 순방향 계산
						o = forward( wh, wo, hi, e[i] );

						// 출력층 가중치 조정
						olearn( wo, hi, e[i], o );

						// 중간층 가중치 조정
						hlearn( wh, wo, hi, e[i], o );

						// 오차 계산
						//  - 데이터 "집합"의 오차를 계산
						//
						// 교사 데이터와의 차이를 계산해서 제곱
						err += ( ( o - e[i][INPUTNO] ) * ( o - e[i][INPUTNO] ) );
					}

					++count;

					// 오차 출력
					printf( "%d\t%lf\n", count, err );
				}

				LF();

				PROCESS_MAIN( print_wh( wh ) );

				LF();

				PROCESS_MAIN( print_wo( wo ) );

				LF();

				// 계산
				for( int i = 0; n_of_e > i; ++i )
				{
					printf( "%2d", i );

					printf( "      input : " );
					for( int j = 0; INPUTNO > j; ++j )
					{
						printf( "%.2lf ", e[i][j] );
					}

					// 순방향 계산
					o = forward( wh, wo, hi, e[i] );
					printf( "      output : %.2lf\n", o );
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}