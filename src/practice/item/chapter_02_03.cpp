#include "chapter_02_03.hpp"

#include <cstdio>
#include <cstdlib>
#include <conio.h>

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"

#include "utility4example.hpp"

namespace chapter_02_03
{
	const int GENMAX = 1000;
	const int NODENO = 15;
	const float ALPHA = 0.1f;		// 학습 계수
	const float GAMMA = 0.9f;		// 할인율
	const float EPSILON = 0.3f;		// 행동 선택 무작위율
	const int RANDOM_SEED = 32767;




	int updateq( const int s, const int qvalue[NODENO] )
	{
		int qv = 0;		// 갱신되는 q 값
		int qmax = 0;	// q 값의 최대 값

		
		//
		// # 개념상 데이터 구조 : 균형 2진 트리
		//           0
		//    1              2
		//  3   4          5   6
		// 7 8 9 10     11 12 13 14
		//
		// # 실제 데이터 구조 : 배열
		// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		//
		
		// 가장 아랫단에 도달
		if( 6 < s )
		{
			// 목표 지점 도달
			if( 14 == s ) // 보상 o
			{
				qv = qvalue[s] + ALPHA * ( 1000 - qvalue[s] );
			}
			//else if( 11 == s ) // 보상 o
			//{
			//	qv = qvalue[s] + ALPHA * ( 500 - qvalue[s] );
			//}
			else // 보상 x
			{
				qv = qvalue[s];
			}
		}
		else
		{
			if( qvalue[2 * s + 1] > qvalue[2 * s + 2] )
			{
				qmax = qvalue[2 * s + 1];
			}
			else
			{
				qmax = qvalue[2 * s + 2];
			}

			// 그저 경로를 지나가는 거라면 다음 노드의 값에 가깝게 보정
			qv = qvalue[s] + ALPHA * ( GAMMA * qmax - qvalue[s] );
		}

		return qv;
	}
	int select_action( const int olds, const int qvalue[NODENO] )
	{
		int s = 0;

		//
		// 입실론 그리디 알고리즘 이용
		//

		// 무작위 행동
		if( EPSILON > u4e::randomf( 0, 1 ) )
		{
			// 왼쪽
			if( u4e::randomi( 0, 1 ) == 0 )
			{
				s = 2 * olds + 1;
			}
			// 오른쪽
			else
			{
				s = 2 * olds + 2;
			}
		}
		// Q 값 이용 : 최댓값 선택
		else
		{
			// 왼쪽
			if( qvalue[2 * olds + 1] > qvalue[2 * olds + 2] )
			{
				s = 2 * olds + 1;
			}
			// 오른쪽
			else
			{
				s = 2 * olds + 2;
			}
		}

		return s;
	}

	void print_q_value( const int qvalue[NODENO] )
	{
		for( int i = 0; NODENO > i; ++i )
		{
			printf( "%d\t", qvalue[i] );
		}
		printf( "\n" );
	}




	r2tm::TitleFunctionT Example::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "practice : 2 - 3";
		};
	}
	r2tm::DoFunctionT Example::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			OUTPUT_NOTE( "강화학습( Q 학습 ) 예제 프로그램" );
			OUTPUT_NOTE( "미로 탐색을 학습합니다." );

			LF();

			OUTPUT_SUBJECT( "처리 과정" );
			OUTPUT_COMMENT( "1. 초기 Q값 목록 난수로 설정" );
			OUTPUT_COMMENT( "2. 노드를 돌며 Q 값을 갱신" );
			OUTPUT_COMMENT( "3. 목표 지점에 도달하면 보상 부여" );

			LF();

			OUTPUT_SUBJECT( "개념상 데이터 구조 : 균형 2진 트리" );
			OUTPUT_COMMENT( "           0" );
			OUTPUT_COMMENT( "    1              2" );
			OUTPUT_COMMENT( "  3   4          5   6" );
			OUTPUT_COMMENT( " 7 8 9 10     11 12 13 14" );

			LF();

			OUTPUT_SUBJECT( "실제 데이터 구조 : 배열" );
			OUTPUT_COMMENT( "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15" );

			LS();

			OUTPUT_STRING( "아무 키 누르면 시작." );
			_getch();

			LS();

			//
			// 난수 초기화
			//
			PROCESS_MAIN( srand( RANDOM_SEED ) );

			LS();

			{
				int s = 0;			// 상태
				int t = 0;			// 시각
				int qvalue[NODENO];	// q값

				//
				// Q 값 초기화
				//
				for( int i = 0; NODENO > i; ++i )
				{
					qvalue[i] = u4e::randomi( 0, 100 );
				}
				print_q_value( qvalue );

				//
				// 학습
				//
				for( int i = 0; GENMAX > i; ++i )
				{
					// 행동 초기화
					s = 0;

					for( t = 0; 3 > t; ++t )
					{
						//  행동 선택
						s = select_action( s, qvalue );

						// Q값 갱신
						qvalue[s] = updateq( s, qvalue );

						print_q_value( qvalue );
					}
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}