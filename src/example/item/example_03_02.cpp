#include "example_03_02.hpp"

#include <cstdio>
#include <cstdlib>
#include <conio.h>

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "utility4example.hpp"

namespace example_03_02
{
	const int MAXVALUE = 100;						// ���Կ� ��ġ�� �ִ�
	const int N = 30;								// �� ����
	const int WEIGHTLIMIT = ( N * MAXVALUE / 4 );	// �߷� ����
	const int POOLSIZE = 30;						// ������
	const int LASTG = 50;							// �� ����
	const double MRATE = 0.01;						// �������� Ȯ��
	const int RANDOM_SEED = 32767;					// ���� �õ�
	const int YES = 1;
	const int NO = 0;

	// ��
	int parcel[N][2];



	// �� �ʱ�ȭ
	bool init_parcel()
	{
		FILE* fp = nullptr;
		if( 0 != fopen_s( &fp, "resources/chapter_03_02.txt", "rb" ) )
		{
			return false;
		}

		// �� �ڵ带 �̷��� ������ �ϴ� �ɱ�?
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

	// ������ ���
	int evalfit( int gene[] )
	{
		int pos = 0;		// ������ ��ġ
		int value = 0;		// �򰫰�
		int weight = 0;		// �߷�

		//
		// �� �����ڰ� ǥ���ϴ� �߷��� �򰫰��� ���
		//
		for( pos = 0; N > pos; ++pos )
		{
			weight += ( parcel[pos][0] * gene[pos] );
			value += ( parcel[pos][1] * gene[pos] );
		}

		//
		// ���� ������ ó�� : �߷� �ʰ�
		//
		if( WEIGHTLIMIT <= weight )
		{
			value = 0;
		}

		return value;
	}

	// �θ� ����
	int select_pool( int roulette[POOLSIZE], int total_fitness )
	{
		int i = 0;
		int ball = 0; // �� ���� ��ġ�� ��ġ
		int acc = 0; // ������ ���� ��� ��

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

	// ����ü 2���� ����
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
	// ����
	void mating(
		  int pool[POOLSIZE][N]
		, int ngpool[POOLSIZE * 2][N]
	)
	{
		int total_fitness = 0;
		int roulette[POOLSIZE];
		int mama = 0;
		int papa = 0;

		// �귿 ����
		for( int i = 0; POOLSIZE > i; ++i )
		{
			roulette[i] = evalfit( pool[i] );

			// ������ �հ� ���
			total_fitness += roulette[i];
		}

		// ���� + ����
		for( int i = 0; POOLSIZE > i; ++i )
		{
			// �θ� ����
			do
			{
				mama = select_pool( roulette, total_fitness );
				papa = select_pool( roulette, total_fitness );
			} while( mama == papa ); //  �θ� ���ٸ� �ٽ� ����

			// ����ü ����
			crossing(
				  N
				, pool[mama]
				, pool[papa]
				, ngpool[i * 2]
				, ngpool[i * 2 + 1]
			);
		}
	}
	// ������ ����
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
	// ��������
	void mutation( int ngpool[POOLSIZE][N] )
	{
		for( int i = 0; POOLSIZE > i; ++i )
		{
			for( int j = 0; N > j; ++j )
			{
				// ���� ��������
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
	// Ǯ ���
	void print_pool( int pool[POOLSIZE][N] )
	{
		int fitness = 0; // ������
		double total_fitness = 0; // ������ �հ�
		int elite = 0;
		int bestfit = 0; // ����Ʈ ������ ó���� ����

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

		// ����Ʈ �������� ������ ���
		printf( "%d\t%d\t", elite, bestfit );
		
		// ��� ������ ���
		printf( "%lf\n", total_fitness / POOLSIZE );
	}
	// �ʱ� ���� ����
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

	// ���� ���� ����
	void select_new_generation(
		  int ngpool[POOLSIZE * 2][N]
		, int pool[POOLSIZE][N]
	)
	{
		int total_fitness = 0;			// ������ �հ�
		int roulette[POOLSIZE * 2];		// ������ ����
		int ball = 0;					// �� : ���� ��ġ�� ��ġ
		int acc = 0;					// ������ ���� ��� ��
		int g = 0;

		// ����ü ���� �� ����
		for( int i = 0; POOLSIZE > i; ++i )
		{
			// �귿 �ۼ�
			total_fitness = 0;
			for( int c = 0; POOLSIZE * 2 > c; ++c )
			{
				roulette[c] = evalfit( ngpool[c] );

				// ������ �հ� ���
				total_fitness += roulette[c];
			}

			// ����ü 1�� ����
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

			// ����ü ����
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

			OUTPUT_NOTE( "��ȭ����( GA ) ���� ó��" );
			OUTPUT_NOTE( "����ü 2�� ���� ó��" );

			LS();

			//
			// ���� �ʱ�ȭ
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

			OUTPUT_NOTE( "��ȭ����( GA )�� �̿��� �賶 ����" );
			OUTPUT_NOTE( "���� ���� �ش��� Ž��" );

			LS();

			int pool[POOLSIZE][N];			// ����ü ����
			int ngpool[POOLSIZE * 2][N];	// ���� ���� ����ü ����
			int generation = 0;					// ���� ���� ��

			// ���� �ʱ�ȭ
			PROCESS_MAIN( srand( RANDOM_SEED ) );

			LF();

			// �� �ʱ�ȭ
			EXPECT_TRUE( init_parcel() );
			PROCESS_MAIN( print_parcel() );

			LF();

			// �ʱ� ���� ����
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