#include "chapter_02_02.hpp"

#include <conio.h>
#include <cstdlib>

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"

namespace chapter_02_02
{
	const int SETSIZE = 100;	// �н� ������ ���� ũ��
	const int CNO = 10;			// �н� ������ �ڸ���( 10�� ȸ�� )
	const int GENMAX = 10000;	// �ش� �ĺ� ���� Ƚ��
	const int RANDOM_SEED = 32767;		// ���� �õ�

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
			for( int j = 0; CNO > j; ++j )
			{
				printf( "%d ", data[i][j] );
			}

			printf( "     %d\n", teacher[i] );
		}
	}

	// ���� ���� : 0, 1, 2
	int rand012()
	{
		int rnd = 0;

		//
		// �� ���ǹ��� �����ϴ� ������
		// ����� ��� rnd ���� RAND_MAX �� ��� 3�� ������ �����̴�.
		//
		while( ( rnd = rand() ) == RAND_MAX );

		//
		// �Ʒ��� �ź�ο� ������ �ñ��ϸ� �ּ��� Ǯ�� Ȯ�� �ض�.
		// 
		//OUTPUT_VALUE( rnd );
		//OUTPUT_VALUE( RAND_MAX * 3 );
		//OUTPUT_VALUE( ( double )rnd / RAND_MAX * 3 );

		return (int)( (double)rnd / RAND_MAX * 3 );
	}

	int calcscore( int data[SETSIZE][CNO], int teacher[SETSIZE], int answer[CNO] )
	{
		int score = 0;	// ����
		int point = 0;	// ��� �����Ͱ� ��ġ �ϸ� +, �����Ͱ� 2�� +

		for( int i = 0; SETSIZE > i; ++i )
		{
			//
			// ��ġ�� ���
			//
			point = 0;
			for( int j = 0; CNO > j; ++j )
			{
				// 2�� ���ϵ� ī�� : ������ ���� ���
				if( answer[j] == 2 )
				{
					++point;
				}
				// ��� �����Ͱ� ��ġ�ϸ� +
				else if( answer[j] == data[i][j] )
				{
					++point;
				}
			}

			//
			// ���� ���
			//

			// ��� ��ġ +
			if( ( point == CNO ) && ( teacher[i] == 1 ) )
			{
				++score;
			}
			// ��� ��ġ +
			else if( ( point != CNO ) && ( teacher[i] == 0 ) )
			{
				++score;
			}
		}

		return score;
	}




	r2tm::TitleFunctionT Example::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "practice : 2 - 2";
		};
	}
	r2tm::DoFunctionT Example::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			OUTPUT_NOTE( "�ܼ��� �ͳ��н� ����" );
			OUTPUT_NOTE( "���� �н���" );

			LF();

			OUTPUT_SUBJECT( "�ְ� ���� ���α׷�" );

			LF();

			OUTPUT_SUBJECT( "������ ����" );
			OUTPUT_COMMENT( "X ȸ�翡 ������ �ִ� 10������ �ְ� ���/�϶� ���� : C" );
			OUTPUT_COMMENT( "X ȸ���� �ְ� ���/�϶� ���� : X" );
			OUTPUT_COMMENT( "c c c c c c c c c c     x" );
			OUTPUT_COMMENT( "c�� �� : ��� 1, �϶� 0 " );
			OUTPUT_COMMENT( "x�� �� : ��� 1, �϶� 0 " );

			LF();

			OUTPUT_SUBJECT( "ó�� ����" );
			OUTPUT_COMMENT( "1. 100 ���� �н� ������ �б�" );
			OUTPUT_COMMENT( "2. ���� ������� �ش� �ĺ� ����" );
			OUTPUT_COMMENT( "3. ������ 10�ڸ� 2���� ���� ��" );
			OUTPUT_COMMENT( "4. 2 ~ 3 �ݺ�" );

			LF();

			OUTPUT_SUBJECT( "�ش� �ĺ��� ���� �� �ִ� ��" );
			OUTPUT_COMMENT( "0 : �϶�" );
			OUTPUT_COMMENT( "1 : ���" );
			OUTPUT_COMMENT( "2 : ����" );

			LS();

			//
			// ���� �ʱ�ȭ
			//
			PROCESS_MAIN( srand( RANDOM_SEED ) );

			LS();

			//
			// �н� ������ ������ �о����
			//
			DECLARATION_MAIN( int data[SETSIZE][CNO] );		// �н� ������ ����
			DECLARATION_MAIN( int teacher[SETSIZE] );		// ���� ������
			EXPECT_TRUE( read_data( data, teacher ) );
			//PROCESS_MAIN( output_data( data, teacher ) );

			LS();

			{
				int answer[CNO];			// �ش� �ĺ�
				int score = 0;
				int bestscore = 0;			// ���� ���� ����
				int bestanswer[CNO];		// Ž�� �� ã�� ���� ���� �ش�
				
				//
				// �ش� �ĺ� ������ �˻�
				//
				for( int i = 0; GENMAX > i; ++i )
				{
					// �ش� �ĺ� ����
					for( int j = 0; CNO > j; ++j )
					{
						answer[j] = rand012();
					}

					// �ش� �ĺ� �˻�
					score = calcscore( data, teacher, answer );

					if( bestscore >= score )
					{
						continue;
					}

					//
					// �ְ� ����/�ش� ����
					//
					
					// ����
					for( int j = 0; CNO > j; ++j )
					{
						bestanswer[j] = answer[j];
					}

					bestscore = score;

					// �ְ� ���� �ش� ���
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