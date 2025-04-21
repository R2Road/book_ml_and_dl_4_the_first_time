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
	const float ALPHA = 0.1f;		// �н� ���
	const float GAMMA = 0.9f;		// ������
	const float EPSILON = 0.3f;		// �ൿ ���� ��������
	const int RANDOM_SEED = 32767;




	int updateq( const int s, const int qvalue[NODENO] )
	{
		int qv = 0;		// ���ŵǴ� q ��
		int qmax = 0;	// q ���� �ִ� ��

		
		//
		// # ����� ������ ���� : ���� 2�� Ʈ��
		//           0
		//    1              2
		//  3   4          5   6
		// 7 8 9 10     11 12 13 14
		//
		// # ���� ������ ���� : �迭
		// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		//
		
		// ���� �Ʒ��ܿ� ����
		if( 6 < s )
		{
			// ��ǥ ���� ����
			if( 14 == s ) // ���� o
			{
				qv = qvalue[s] + ALPHA * ( 1000 - qvalue[s] );
			}
			//else if( 11 == s ) // ���� o
			//{
			//	qv = qvalue[s] + ALPHA * ( 500 - qvalue[s] );
			//}
			else // ���� x
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

			// ���� ��θ� �������� �Ŷ�� ���� ����� ���� ������ ����
			qv = qvalue[s] + ALPHA * ( GAMMA * qmax - qvalue[s] );
		}

		return qv;
	}
	int select_action( const int olds, const int qvalue[NODENO] )
	{
		int s = 0;

		//
		// �ԽǷ� �׸��� �˰��� �̿�
		//

		// ������ �ൿ
		if( EPSILON > u4e::randomf( 0, 1 ) )
		{
			// ����
			if( u4e::randomi( 0, 1 ) == 0 )
			{
				s = 2 * olds + 1;
			}
			// ������
			else
			{
				s = 2 * olds + 2;
			}
		}
		// Q �� �̿� : �ִ� ����
		else
		{
			// ����
			if( qvalue[2 * olds + 1] > qvalue[2 * olds + 2] )
			{
				s = 2 * olds + 1;
			}
			// ������
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

			OUTPUT_NOTE( "��ȭ�н�( Q �н� ) ���� ���α׷�" );
			OUTPUT_NOTE( "�̷� Ž���� �н��մϴ�." );

			LF();

			OUTPUT_SUBJECT( "ó�� ����" );
			OUTPUT_COMMENT( "1. �ʱ� Q�� ��� ������ ����" );
			OUTPUT_COMMENT( "2. ��带 ���� Q ���� ����" );
			OUTPUT_COMMENT( "3. ��ǥ ������ �����ϸ� ���� �ο�" );

			LF();

			OUTPUT_SUBJECT( "����� ������ ���� : ���� 2�� Ʈ��" );
			OUTPUT_COMMENT( "           0" );
			OUTPUT_COMMENT( "    1              2" );
			OUTPUT_COMMENT( "  3   4          5   6" );
			OUTPUT_COMMENT( " 7 8 9 10     11 12 13 14" );

			LF();

			OUTPUT_SUBJECT( "���� ������ ���� : �迭" );
			OUTPUT_COMMENT( "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15" );

			LS();

			OUTPUT_STRING( "�ƹ� Ű ������ ����." );
			_getch();

			LS();

			//
			// ���� �ʱ�ȭ
			//
			PROCESS_MAIN( srand( RANDOM_SEED ) );

			LS();

			{
				int s = 0;			// ����
				int t = 0;			// �ð�
				int qvalue[NODENO];	// q��

				//
				// Q �� �ʱ�ȭ
				//
				for( int i = 0; NODENO > i; ++i )
				{
					qvalue[i] = u4e::randomi( 0, 100 );
				}
				print_q_value( qvalue );

				//
				// �н�
				//
				for( int i = 0; GENMAX > i; ++i )
				{
					// �ൿ �ʱ�ȭ
					s = 0;

					for( t = 0; 3 > t; ++t )
					{
						//  �ൿ ����
						s = select_action( s, qvalue );

						// Q�� ����
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