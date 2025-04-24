#include "example_03_01.hpp"

#include <cstdio>
#include <cstdlib>
#include <conio.h>

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "utility4example.hpp"

namespace example_03_01
{
	const int NOA = 10;				// 개미 개체 수
	const int ILIMIT = 50;			// 반복 횟수
	const int Q = 3;				// 페로몬 갱신 상수
	const float RHO = 0.8f;			// 증발 상수
	const int STEP = 10;			// 길 선택 단계 수
	const float EPSILON = 0.15f;	// 행동 선택 무작위 확률
	const int RANDOM_SEED = 32768;

	void print_pheromone( const double pheromone[2][STEP] )
	{
		for( int i = 0; 2 > i; ++i )
		{
			for( int j = 0; STEP > j; ++j )
			{
				printf( "%4.2lf ", pheromone[i][j] );
			}
			printf( "\n" );
		}
	}
	void print_mstep( const int mstep[NOA][STEP] )
	{
		for( int i = 0; NOA > i; ++i )
		{
			for( int j = 0; STEP > j; ++j )
			{
				printf( "%d", mstep[i][j] );
			}
			printf( "\n" );
		}
	}

	void walk(
		  double pheromone[2][STEP]
		, int mstep[NOA][STEP]
	)
	{
		for( int m = 0; NOA > m; ++m )
		{
			for( int s = 0; STEP > s; ++s )
			{
				// 입실론 그리디
				
				// 무작위 행동
				if( EPSILON > u4e::randomf( 0, 1 ) || 1e-9 > abs( pheromone[0][s] - pheromone[1][s] ) )
				{
					mstep[m][s] = u4e::randomi( 0, 1 );
				}
				// 페로몬 농도에 따른 선택
				else
				{
					if( pheromone[0][s] > pheromone[1][s] )
					{
						mstep[m][s] = 0;
					}
					else
					{
						mstep[m][s] = 1;
					}
				}
			}
		}

		// 개미의 행동 출력
		print_mstep( mstep );
	}
	void update_pheromone(
		  const int cost[2][STEP]
		, double pheromone[2][STEP]
		, int mstep[NOA][STEP]
	)
	{
		int lm = 0; // 개미가 걸은 거리
		double sum_lm = 0; // 개미가 걸은 합계 거리

		// 페로몬 증발
		for( int i = 0; 2 > i; ++i )
		{
			for( int j = 0; STEP > j; ++j )
			{
				pheromone[i][j] *= RHO;
			}
		}

		// 개미에 의한 덧칠
		for( int m = 0; NOA > m; ++m )
		{
			// 개미의 총 이동 거리 계산
			lm = 0;
			for( int i = 0; STEP > i; ++i )
			{
				lm += cost[mstep[m][i]][i];
			}

			// 페로몬 덧칠
			for( int i = 0; STEP > i; ++i )
			{
				pheromone[mstep[m][i]][i] += Q * ( 1.0 / lm );
			}

			sum_lm += lm;
		}

		// 개미가 걸은 평균 거리 출력
		printf( "distance : %lf\n", sum_lm / NOA );
	}



	r2tm::TitleFunctionT Do::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "example : 3 - 1 : Do";
		};
	}
	r2tm::DoFunctionT Do::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			OUTPUT_NOTE( "개미무리 최적화법( aco ) 예제 프로그램" );
			OUTPUT_NOTE( "aco를 이용하여 최적값을 학습" );

			LS();

			//
			// 난수 초기화
			//
			PROCESS_MAIN( srand( RANDOM_SEED ) );

			LS();

			{
				const int cost[2][STEP] = {
					  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
					, { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 }
				};
				double pheromone[2][STEP] = { 0 };
				int mstep[NOA][STEP];

				//
				for( int i = 0; ILIMIT > i; ++i )
				{
					// 페로몬 상태 출력
					printf( "%d : \n", i );
					print_pheromone( pheromone );

					// 개미 이동
					walk( pheromone, mstep );

					// 페로몬 갱신
					update_pheromone( cost, pheromone, mstep );

					printf( "----------------------------\n" );
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}