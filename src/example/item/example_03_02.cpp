#include "example_03_02.hpp"

#include <cstdio>
#include <cstdlib>
#include <conio.h>

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "utility4example.hpp"

namespace example_03_02
{
	const int MAXVALUE = 100;						// 무게와 가치의 최댓값
	const int N = 30;								// 짐 개수
	const int WEIGHTLIMIT = ( N * MAXVALUE / 4 );	// 중량 제한
	const int POOLSIZE = 30;						// 유전자
	const int LASTG = 50;							// 끝 세대
	const double MRATE = 0.01;						// 돌연변이 확률
	const int RANDOM_SEED = 32767;					// 난수 시드
	const int YES = 1;
	const int NO = 0;

	// 짐
	int parcel[N][2];



	// 짐 초기화
	bool init_parcel()
	{
		FILE* fp = nullptr;
		if( 0 != fopen_s( &fp, "resources/chapter_03_02.txt", "rb" ) )
		{
			return false;
		}

		// 꼭 코드를 이렇게 만들어야 하는 걸까?
		for( int i = 0;
			  ( N > i )
			&& EOF != fscanf_s( fp, "%d %d", &parcel[i][0], &parcel[i][1] );
			++i
		);

		return true;
	}
	void print_parcel()
	{
		printf( "# Parcel List\n" );
		for( int i = 0; N > i; ++i )
		{
			printf( "   NO.%2d     weight : %3d      value : %3d\n", i, parcel[i][0], parcel[i][1] );
		}
	}

	// 적응도 계산
	int evalfit( int gene[] )
	{
		int pos = 0;		// 유전자 위치
		int value = 0;		// 평갓값
		int weight = 0;		// 중량

		//
		// 각 유전자가 표현하는 중량과 평갓값을 계산
		//
		for( pos = 0; N > pos; ++pos )
		{
			weight += ( parcel[pos][0] * gene[pos] );
			value += ( parcel[pos][1] * gene[pos] );
		}

		//
		// 죽은 유전자 처리 : 중량 초과
		//
		if( WEIGHTLIMIT <= weight )
		{
			value = 0;
		}

		return value;
	}

	// 부모 선택
	int select_pool( int roulette[POOLSIZE], int total_fitness )
	{
		int i = 0;
		int ball = 0; // 공 선택 위치의 수치
		int acc = 0; // 적응도 누적 계산 값

		ball = u4e::randomi( 0, total_fitness - 1 );
		for( i = 0; POOLSIZE > i; ++i )
		{
			acc += roulette[i];
			if( acc > ball )
			{
				break;
			}
		}

		return i;
	}

	// 염색체 2개를 교차
	void crossing( const int length, const int mama[], const int papa[], int child_1[], int child_2[] )
	{
		const int crossing_point = u4e::randomi( 0, length - 1 );

		int j = 0;
		for( ; crossing_point > j; ++j )
		{
			child_1[j] = mama[j];
			child_2[j] = papa[j];
		}

		for( ; length > j; ++j )
		{
			child_1[j] = papa[j];
			child_2[j] = mama[j];
		}
	}
	// 교차
	void mating(
		  int pool[POOLSIZE][N]
		, int ngpool[POOLSIZE * 2][N]
	)
	{
		int total_fitness = 0;
		int roulette[POOLSIZE];
		int mama = 0;
		int papa = 0;

		// 룰렛 생성
		for( int i = 0; POOLSIZE > i; ++i )
		{
			roulette[i] = evalfit( pool[i] );

			// 적응도 합계 계산
			total_fitness += roulette[i];
		}

		// 선택 + 교차
		for( int i = 0; POOLSIZE > i; ++i )
		{
			// 부모 선택
			do
			{
				mama = select_pool( roulette, total_fitness );
				papa = select_pool( roulette, total_fitness );
			} while( mama == papa ); //  부모가 같다면 다시 선택

			// 염색체 교차
			crossing(
				  N
				, pool[mama]
				, pool[papa]
				, ngpool[i * 2]
				, ngpool[i * 2 + 1]
			);
		}
	}
	// 진릿값 반전
	int notval( int v )
	{
		if( v == YES )
		{
			return NO;
		}
		else
		{
			return YES;
		}
	}
	// 돌연변이
	void mutation( int ngpool[POOLSIZE][N] )
	{
		for( int i = 0; POOLSIZE > i; ++i )
		{
			for( int j = 0; N > j; ++j )
			{
				// 반전 돌연변이
				ngpool[i][j] = notval( ngpool[i][j] );
			}
		}
	}


	void print_gene( const int length, const int gene[] )
	{
		for( int i = 0; length > i; ++i )
		{
			printf( "%d", gene[i] );
		}
		printf( "\n" );
	}
	// 풀 출력
	void print_pool( int pool[POOLSIZE][N] )
	{
		int fitness = 0; // 적응도
		double total_fitness = 0; // 적응도 합계
		int elite = 0;
		int bestfit = 0; // 엘리트 유전자 처리용 변수

		for( int i = 0; POOLSIZE > i; ++i )
		{
			for( int j = 0; N > j; ++j )
			{
				printf( "%1d", pool[i][j] );
			}

			fitness = evalfit( pool[i] );
			printf( "\t%d\n", fitness );
			if( fitness > bestfit )
			{
				bestfit = fitness;
				elite = i;
			}

			total_fitness += fitness;
		}

		// 엘리트 유전자의 적응도 출력
		printf( "%d\t%d\t", elite, bestfit );
		
		// 평균 적응도 출력
		printf( "%lf\n", total_fitness / POOLSIZE );
	}
	// 초기 집단 생성
	void init_pool( int pool[POOLSIZE][N] )
	{
		for( int i = 0; POOLSIZE > i; ++i )
		{
			for( int j = 0; N > j; ++j )
			{
				pool[i][j] = u4e::randomi( 0, 1 );
			}
		}
	}

	// 다음 세대 선택
	void select_new_generation(
		  int ngpool[POOLSIZE * 2][N]
		, int pool[POOLSIZE][N]
	)
	{
		int total_fitness = 0;			// 적응도 합계
		int roulette[POOLSIZE * 2];		// 적응도 저장
		int ball = 0;					// 공 : 선택 위치의 수치
		int acc = 0;					// 적응도 누적 계산 값
		int g = 0;

		// 염색체 선택 후 복사
		for( int i = 0; POOLSIZE > i; ++i )
		{
			// 룰렛 작성
			total_fitness = 0;
			for( int c = 0; POOLSIZE * 2 > c; ++c )
			{
				roulette[c] = evalfit( ngpool[c] );

				// 적응도 합계 계산
				total_fitness += roulette[c];
			}

			// 염색체 1개 선택
			ball = u4e::randomi( 0, total_fitness - 1 );
			acc = 0;
			for( int c = 0; POOLSIZE * 2 > c; ++c )
			{
				acc += roulette[c];
				if( acc > ball )
				{
					g = c;
					break;
				}
			}

			// 염색체 복사
			for( int j = 0; N > j; ++j )
			{
				pool[i][j] = ngpool[g][j];
			}
		}
	}



	r2tm::TitleFunctionT Crossing::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "example : 3 - 2 : Crossing";
		};
	}
	r2tm::DoFunctionT Crossing::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			OUTPUT_NOTE( "진화연산( GA ) 교차 처리" );
			OUTPUT_NOTE( "염색체 2개 교차 처리" );

			LS();

			//
			// 난수 초기화
			//
			PROCESS_MAIN( srand( RANDOM_SEED ) );

			LS();

			DECLARATION_MAIN( const int length = 10 );
			DECLARATION_MAIN( int m[length] );
			DECLARATION_MAIN( int p[length] );
			DECLARATION_MAIN( int c1[length] );
			DECLARATION_MAIN( int c2[length] );

			LF();

			PROCESS_MAIN( for( int i = 0; length > i; ++i ) m[i] = 1 );
			PROCESS_MAIN( memset( p, 0, sizeof( p ) ) );

			LF();

			print_gene( length, m );
			print_gene( length, p );

			LS();

			{
				for( int i = 0; 6 > i; ++i )
				{
					PROCESS_MAIN( crossing( length, m, p, c1, c2 ) );
					print_gene( length, c1 );
					print_gene( length, c2 );

					LF();
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Do::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "example : 3 - 2";
		};
	}
	r2tm::DoFunctionT Do::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			OUTPUT_NOTE( "진화연산( GA )를 이용한 배낭 문제" );
			OUTPUT_NOTE( "가장 좋은 해답을 탐색" );

			LS();

			int pool[POOLSIZE][N];			// 염색체 집단
			int ngpool[POOLSIZE * 2][N];	// 다음 세대 염색체 집단
			int generation = 0;					// 현재 세대 수

			// 난수 초기화
			PROCESS_MAIN( srand( RANDOM_SEED ) );

			LF();

			// 짐 초기화
			EXPECT_TRUE( init_parcel() );
			PROCESS_MAIN( print_parcel() );

			LF();

			// 초기 집단 생성
			PROCESS_MAIN( init_pool( pool ) );

			LS();

			{
				for( int generation = 0; LASTG > generation; ++generation )
				{
					printf( "G : %2d\n", generation );

					mating( pool, ngpool );
					mutation( ngpool );
					select_new_generation( ngpool, pool );
					print_pool( pool );
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}