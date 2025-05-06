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

	// ���� ���
	void print_filter( const double filter[FILTERSIZE][FILTERSIZE] )
	{
		for( int i = 0; FILTERSIZE > i; ++i )
		{
			printf( "    " );
			for( int j = 0; FILTERSIZE > j; ++j )
			{
				printf( "%.3lf  ", filter[i][j] );
			}
			printf( "\n" );
		}
	}
	void make_filter( const int type, const double filter[FILTERSIZE][FILTERSIZE] )
	{
		static const double f1[FILTERSIZE][FILTERSIZE] = { { 0, 0, 0 }, { 1, 1, 1 }, { 0, 0, 0 } }; // ���� ����
		static const double f2[FILTERSIZE][FILTERSIZE] = { { 0, 1, 0 }, { 0, 1, 0 }, { 0, 1, 0 } }; // ���� ����

		switch( type )
		{
		case 'w': // ����
			memcpy_s( (void*)filter, sizeof( double ) * FILTERSIZE * FILTERSIZE, f1, sizeof( double ) * FILTERSIZE * FILTERSIZE );
			break;
		case 'q': // ����
		case 'e': // �밢��
			memcpy_s( ( void* )filter, sizeof( double ) * FILTERSIZE * FILTERSIZE, f2, sizeof( double ) * FILTERSIZE * FILTERSIZE );
			break;
		}
	}



	// �ռ��� ��� ���
	void print_conv( double convout[][INPUTSIZE] )
	{
		for( int i = 1; INPUTSIZE - 1 > i; ++i )
		{
			printf( "    " );
			for( int j = 1; INPUTSIZE - 1 > j; ++j )
			{
				printf( "%.3lf  ", convout[i][j] );
			}
			printf( "\n" );
		}
	}
	// ���� ����
	double calcconv(
		  const double filter[][FILTERSIZE]
		, double e[][INPUTSIZE]
		, int i
		, int j
	)
	{
		double sum = 0;	// �հ谪

		for( int m = 0; FILTERSIZE > m; ++m )
		{
			for( int n = 0; FILTERSIZE > n; ++n )
			{
				sum += e[i - FILTERSIZE / 2 + m][j - FILTERSIZE / 2 + n] * filter[m][n];
			}
		}

		return sum;
	}
	// �ռ��� ���
	void conv(
		  const double filter[][FILTERSIZE]
		, double e[][INPUTSIZE]
		, double convout[][INPUTSIZE]
	)
	{
		// �ռ��� ������ ����
		const int startpoint = FILTERSIZE / 2;

		for( int i = startpoint; INPUTSIZE - startpoint > i; ++i )
		{
			for( int j = startpoint; INPUTSIZE - startpoint > j; ++j )
			{
				convout[i][j] = calcconv( filter, e, i, j );
			}
		}
	}
	


	// Ǯ�� ��� ���
	void print_pool( double poolout[][POOLOUTSIZE] )
	{
		for( int i = 0; POOLOUTSIZE > i; ++i )
		{
			printf( "    " );
			for( int j = 0; POOLOUTSIZE > j; ++j )
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
	int load_input( const int type, double e[][INPUTSIZE] )
	{
		int n_of_e = 0; // ������ ���� ����

		const char* file_path = nullptr;
		switch( type )
		{
		case 'q': // ����
			file_path = "resources/chapter_05_01_01.txt";
			break;
		case 'w': // ����
			file_path = "resources/chapter_05_01_02.txt";
			break;
		case 'e': // �밢��
			file_path = "resources/chapter_05_01_03.txt";
			break;
		}

		FILE* fp = nullptr;
		if( 0 != fopen_s( &fp, file_path, "rb" ) )
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

			DECLARATION_MAIN( int n_of_e );
			DECLARATION_MAIN( double e[INPUTSIZE][INPUTSIZE] ); // ������ ����

			SS();

			PROCESS_MAIN( n_of_e = load_input( 'q', e ) );
			OUTPUT_VALUE( n_of_e );
			PROCESS_MAIN( print_input( n_of_e, e ) );

			SS();

			PROCESS_MAIN( n_of_e = load_input( 'w', e ) );
			OUTPUT_VALUE( n_of_e );
			PROCESS_MAIN( print_input( n_of_e, e ) );

			SS();

			PROCESS_MAIN( n_of_e = load_input( 'e', e ) );
			OUTPUT_VALUE( n_of_e );
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

			OUTPUT_NOTE( "�ռ����� Ǯ�� ó��" );
			OUTPUT_NOTE( "2���� �����͸� �о�鿩 �ռ����� Ǯ���� �ǽ�" );

			LF();

			OUTPUT_SUBJECT( "�۾� ����" );
			OUTPUT_COMMENT( "�ռ����� �����ϴ� ���� �ʱ�ȭ" );
			OUTPUT_COMMENT( "�ռ��� ���" );
			OUTPUT_COMMENT( "   ������ �Է� ������ ��ü ������ ���� �ݺ�" );
			OUTPUT_COMMENT( "   1. ������ �� ���� �Է� �������� �������� ���� ȭ�Ҹ��� �������� ���" );
			OUTPUT_COMMENT( "   2. �տ��� ���� ���� ���� �־� ��� �����Ϳ� �߰�" );
			OUTPUT_COMMENT( "Ǯ�� ���" );
			OUTPUT_COMMENT( "��� ���" );

			LS();

			OUTPUT_SUBJECT( "�۵� ������ ����" );
			OUTPUT_COMMENT( "Q. ����" );
			OUTPUT_COMMENT( "W. ����" );
			OUTPUT_COMMENT( "E. �밢��" );
			int type = 0;
			while( !( 'q' == type || 'w' == type || 'e' == type ) )
			{
				type = _getch();
			}

			LS();

			{
				DECLARATION_MAIN( double filter[FILTERSIZE][FILTERSIZE] );
				PROCESS_MAIN( make_filter( type, filter ) );
				PROCESS_MAIN( print_filter( filter ) );

				LF();

				DECLARATION_MAIN( double e[INPUTSIZE][INPUTSIZE] ); // ������ ����
				DECLARATION_MAIN( const int n_of_e = load_input( type, e ) );
				OUTPUT_VALUE( n_of_e );
				PROCESS_MAIN( print_input( n_of_e, e ) );

				LF();

				double convout[INPUTSIZE][INPUTSIZE] = { 0 };	// �ռ��� ���
				double poolout[POOLOUTSIZE][POOLOUTSIZE];		// ��� ������

				LF();

				// �ռ��� ���
				PROCESS_MAIN( conv( filter, e, convout ) );
				PROCESS_MAIN( print_conv( convout ) );
				
				LF();

				// Ǯ�� ���
				PROCESS_MAIN( pool( convout, poolout ) );

				LF();

				// ��� ���
				PROCESS_MAIN( print_pool( poolout ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}