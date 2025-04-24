#include "example_02_02.hpp"

#include <conio.h>
#include <cstdlib>

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"

#include "utility4example.hpp"

namespace example_02_02
{
	const int SETSIZE = 100;	// 학습 데이터 집합 크기
	const int CNO = 10;			// 학습 데이터 자릿수( 10개 회사 )
	const int GENMAX = 10000;	// 해답 후보 생성 횟수
	const int RANDOM_SEED = 32767;		// 난수 시드

	bool read_data( int data[SETSIZE][CNO], int teacher[SETSIZE] )
	{
		FILE* fp = nullptr;
		if( 0 != fopen_s( &fp, "resources/chapter_02_02.txt", "rb" ) )
		{
			return false;
		}

		//
		// # Data Format
		// "x x x x x x x x x x    result"
		// x : 0, 1
		// result : 0, 1, 2
		//
		for( int i = 0; SETSIZE > i; ++i )
		{
			for( int j = 0; CNO > j; ++j )
			{
				fscanf_s( fp, "%d", &data[i][j] );
			}

			fscanf_s( fp, "%d", &teacher[i] );
		}

		fclose( fp );

		return true;
	}
	void output_data( const int data[SETSIZE][CNO], const int teacher[SETSIZE] )
	{
		for( int i = 0; SETSIZE > i; ++i )
		{
			printf( "%3d :   ", i );

			for( int j = 0; CNO > j; ++j )
			{
				printf( "%d ", data[i][j] );
			}

			printf( "     %d\n", teacher[i] );
		}
	}

	int calcscore( int data[SETSIZE][CNO], int teacher[SETSIZE], int answer[CNO] )
	{
		int score = 0;	// 점수
		int point = 0;	// 답과 데이터가 일치 하면 +, 데이터가 2면 +

		for( int i = 0; SETSIZE > i; ++i )
		{
			//
			// 일치도 계산
			//
			point = 0;
			for( int j = 0; CNO > j; ++j )
			{
				// 2는 와일드 카드 : 무조건 점수 상승
				if( answer[j] == 2 )
				{
					++point;
				}
				// 답과 데이터가 일치하면 +
				else if( answer[j] == data[i][j] )
				{
					++point;
				}
			}

			//
			// 점수 계산
			//

			// 모두 일치 +
			if( ( point == CNO ) && ( teacher[i] == 1 ) )
			{
				++score;
			}
			// 모두 일치 +
			else if( ( point != CNO ) && ( teacher[i] == 0 ) )
			{
				++score;
			}
		}

		return score;
	}



	r2tm::TitleFunctionT LoadData::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "example : 2 - 2 : Load Data";
		};
	}
	r2tm::DoFunctionT LoadData::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			OUTPUT_COMMENT( "학습 데이터 읽기" );

			LS();

			DECLARATION_MAIN( int data[SETSIZE][CNO] );		// 학습 데이터 집합
			DECLARATION_MAIN( int teacher[SETSIZE] );		// 교사 데이터

			LS();

			//
			// 학습 데이터 집합을 읽어들임
			//
			EXPECT_TRUE( read_data( data, teacher ) );
			PROCESS_MAIN( output_data( data, teacher ) );

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Do::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "example : 2 - 2 : Do";
		};
	}
	r2tm::DoFunctionT Do::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			OUTPUT_NOTE( "단순한 귀납학습 예제" );
			OUTPUT_NOTE( "패턴 학습기" );

			LF();

			OUTPUT_SUBJECT( "주가 예상 프로그램" );

			LF();

			OUTPUT_SUBJECT( "데이터 포맷" );
			OUTPUT_COMMENT( "X 회사에 영향을 주는 10개사의 주가 상승/하락 정보 : C" );
			OUTPUT_COMMENT( "X 회사의 주가 상승/하락 정보 : X" );
			OUTPUT_COMMENT( "c c c c c c c c c c     x" );
			OUTPUT_COMMENT( "c의 값 : 상승 1, 하락 0 " );
			OUTPUT_COMMENT( "x의 값 : 상승 1, 하락 0 " );

			LF();

			OUTPUT_SUBJECT( "처리 과정" );
			OUTPUT_COMMENT( "1. 100 개의 학습 데이터 읽기" );
			OUTPUT_COMMENT( "2. 난수 생성기로 해답 후보 생성" );
			OUTPUT_COMMENT( "3. 적합한 10자리 2진수 패턴 평가" );
			OUTPUT_COMMENT( "4. 2 ~ 3 반복" );

			LF();

			OUTPUT_SUBJECT( "해답 후보가 가질 수 있는 값" );
			OUTPUT_COMMENT( "0 : 하락" );
			OUTPUT_COMMENT( "1 : 상승" );
			OUTPUT_COMMENT( "2 : 무관" );

			LS();

			//
			// 난수 초기화
			//
			PROCESS_MAIN( srand( RANDOM_SEED ) );

			LS();

			//
			// 학습 데이터 집합을 읽어들임
			//
			DECLARATION_MAIN( int data[SETSIZE][CNO] );		// 학습 데이터 집합
			DECLARATION_MAIN( int teacher[SETSIZE] );		// 교사 데이터
			EXPECT_TRUE( read_data( data, teacher ) );
			//PROCESS_MAIN( output_data( data, teacher ) );

			LS();

			{
				int answer[CNO];			// 해답 후보
				int score = 0;
				int bestscore = 0;			// 가장 좋은 점수
				int bestanswer[CNO];		// 탐색 중 찾은 가장 좋은 해답
				
				//
				// 해답 후보 생성과 검사
				//
				for( int i = 0; GENMAX > i; ++i )
				{
					// 해답 후보 생성
					for( int j = 0; CNO > j; ++j )
					{
						answer[j] = u4e::randomi( 0, 2 );
					}

					// 해답 후보 검사
					score = calcscore( data, teacher, answer );

					if( bestscore >= score )
					{
						continue;
					}

					//
					// 최고 점수/해답 갱신
					//
					
					// 복사
					for( int j = 0; CNO > j; ++j )
					{
						bestanswer[j] = answer[j];
					}

					bestscore = score;

					// 최고 점수 해답 출력
					for( int j = 0; CNO > j; ++j )
					{
						printf( "%d ", bestanswer[j] );
					}
					printf( "    : score = %d\n", bestscore );
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}