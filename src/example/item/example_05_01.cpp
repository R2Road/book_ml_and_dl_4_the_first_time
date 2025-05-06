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
	const int INPUTSIZE = 11;	// �Է� ��
	const int FILTERSIZE = 3;	// ���� ũ��
	const int POOLSIZE = 3;		// Ǯ�� ũ��
	const int POOLOUTSIZE = 3;	// Ǯ�� ��� ũ��

	// �ռ��� ��� ���
	void print_conv( double convout[][INPUTSIZE] )
	{
		for( int i = 0; INPUTSIZE > i; ++i )
		{
			printf( "    " );
			for( int j = 0; INPUTSIZE + 1 > j; ++j )
			{
				printf( "%.3lf  ", convout[i][j] );
			}
			printf( "\n" );
		}
	}
	// �ռ��� ���
	void conv(
		  double filter[][FILTERSIZE]
		, double e[][INPUTSIZE]
		, double convout[][INPUTSIZE]
	)
	{
		filter;
		e;
		convout;
	}
	// ���� ����
	double calcconv(
		  double filter[][FILTERSIZE]
		, double e[][INPUTSIZE]
		, int i
		, int j
	)
	{
		filter;
		e;
		i;
		j;

		return 0;
	}


	// Ǯ�� ��� ���
	void print_pool( double poolout[][POOLOUTSIZE] )
	{
		for( int i = 0; POOLOUTSIZE > i; ++i )
		{
			printf( "    " );
			for( int j = 0; POOLOUTSIZE + 1 > j; ++j )
			{
				printf( "%.3lf  ", poolout[i][j] );
			}
			printf( "\n" );
		}
	}
	// �ִ� Ǯ��
	double maxpooling(
		  double convout[][INPUTSIZE]
		, int i
		, int j
	)
	{
		const int halfpool = POOLSIZE / 2;	// Ǯ�� ũ���� 1/2

		// �ִ�
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
	// Ǯ�� ���
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
	



	// ������ �о���̱�
	int load_input( double e[][INPUTSIZE] )
	{
		int n_of_e = 0; // ������ ���� ����

		FILE* fp = nullptr;
		if( 0 != fopen_s( &fp, "resources/chapter_05_01.txt", "rb" ) )
		{
			return 0;
		}

		// �� �ڵ带 �̷��� ������ �ϴ� �ɱ�?
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

			OUTPUT_NOTE( "������ �б�" );

			LS();

			DECLARATION_MAIN( double e[INPUTSIZE][INPUTSIZE] ); // ������ ����

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
			return "example : 5 - 1 : Do";
		};
	}
	r2tm::DoFunctionT Do::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			

			LS();

			{
				
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}