#include "example_03_01.hpp"

#include <cstdio>
#include <cstdlib>
#include <conio.h>

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "utility4example.hpp"

namespace example_03_01
{
	const int NOA = 10;				// ���� ��ü ��
	const int ILIMIT = 50;			// �ݺ� Ƚ��
	const int Q = 3;				// ��θ� ���� ���
	const float RHO = 0.8f;			// ���� ���
	const int STEP = 10;			// �� ���� �ܰ� ��
	const float EPSILON = 0.15f;	// �ൿ ���� ������ Ȯ��
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
				// �ԽǷ� �׸���
				
				// ������ �ൿ
				if( EPSILON > u4e::randomf( 0, 1 ) || 1e-9 > abs( pheromone[0][s] - pheromone[1][s] ) )
				{
					mstep[m][s] = u4e::randomi( 0, 1 );
				}
				// ��θ� �󵵿� ���� ����
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

		// ������ �ൿ ���
		print_mstep( mstep );
	}
	void update_pheromone(
		  const int cost[2][STEP]
		, double pheromone[2][STEP]
		, int mstep[NOA][STEP]
	)
	{
		int lm = 0; // ���̰� ���� �Ÿ�
		double sum_lm = 0; // ���̰� ���� �հ� �Ÿ�

		// ��θ� ����
		for( int i = 0; 2 > i; ++i )
		{
			for( int j = 0; STEP > j; ++j )
			{
				pheromone[i][j] *= RHO;
			}
		}

		// ���̿� ���� ��ĥ
		for( int m = 0; NOA > m; ++m )
		{
			// ������ �� �̵� �Ÿ� ���
			lm = 0;
			for( int i = 0; STEP > i; ++i )
			{
				lm += cost[mstep[m][i]][i];
			}

			// ��θ� ��ĥ
			for( int i = 0; STEP > i; ++i )
			{
				pheromone[mstep[m][i]][i] += Q * ( 1.0 / lm );
			}

			sum_lm += lm;
		}

		// ���̰� ���� ��� �Ÿ� ���
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

			OUTPUT_NOTE( "���̹��� ����ȭ��( aco ) ���� ���α׷�" );
			OUTPUT_NOTE( "aco�� �̿��Ͽ� �������� �н�" );

			LS();

			//
			// ���� �ʱ�ȭ
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
					// ��θ� ���� ���
					printf( "%d : \n", i );
					print_pheromone( pheromone );

					// ���� �̵�
					walk( pheromone, mstep );

					// ��θ� ����
					update_pheromone( cost, pheromone, mstep );

					printf( "----------------------------\n" );
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}