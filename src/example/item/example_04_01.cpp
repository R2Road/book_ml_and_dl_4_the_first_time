#include "example_04_01.hpp"

#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <math.h> // exp

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "utility4example.hpp"

namespace example_04_01
{
	const int INPUTNO = 2;			// �Է� ����
	const int MAXINPUTNO = 100;		// �������� �ִ� ����



	// ����ġ�� ���ΰ� �ʱ�ȭ
	void init_w( double w[INPUTNO + 1] )
	{
		// ����ġ
		w[0] = 1;
		w[1] = 1;

		// ���ΰ�
		w[2] = 1.5;
		// w[2] = 0.5;
	}
	void print_w( double w[INPUTNO + 1] )
	{
		for( int i = 0; INPUTNO + 1 > i; ++i )
		{
			printf( "%.2f  ", w[i] );
		}
		printf( "\n" );
	}

	// ������ �б�
	int getdata( double e[][INPUTNO] )
	{
		int n_of_e = 0; // ������ ���� ����

		FILE* fp = nullptr;
		if( 0 != fopen_s( &fp, "resources/chapter_04_01.txt", "rb" ) )
		{
			return false;
		}

		// �� �ڵ带 �̷��� ������ �ϴ� �ɱ�?
		int i = 0;
		while( EOF != fscanf_s( fp, "%lf", &e[n_of_e][i] ) )
		{
			++i;
			if( INPUTNO <= i )
			{
				i = 0;
				++n_of_e;
			}
		}

		return n_of_e;
	}
	void print_data( const int count, double e[][INPUTNO] )
	{
		printf( "# Data List\n" );
		for( int i = 0; count > i; ++i )
		{
			printf( "    %.3f   %.2f\n", e[i][0], e[i][1] );
		}
	}



	// ���� �Լ�( Ȱ���Լ� ��� �ϴµ�. Activation Function )
	double f( double u )
	{
		// ��� �Լ�
		if( 0 <= u )
		{
			return 1.0;
		}
		else
		{
			return 0.0;
		}

		// �ñ׸��̵� �Լ�
		//
		// exp
		// - �ڿ� ��� e�� ������ ����� ��ȯ�ϴ� �Լ�
		// - e^arg
		//return 1.0 / ( 1.0 + exp( -u ) ) ; // �ñ׸��̵� �Լ� �״���� ǥ��
	}
	// ������ ���
	double forward( double w[INPUTNO + 1], double e[INPUTNO] )
	{
		int i = 0;
		double u = 0; // �߰� ��갪
		double o = 0; // ��°�

		//
		// ���
		// 
		
		// 1 �ܰ�
		// - ������ �Է¿� ����ġ�� ���Ѵ�.
		// - �� ����� ��� ���Ѵ�.
		//
		for( i = 0; INPUTNO > i; ++i )
		{
			u += e[i] * w[i];
		}

		// 2 �ܰ�
		// - ���ΰ� ó��
		// 
		// �� �ڵ带 �� ������ �ۼ��ؾ� �ϳ�? ��.
		u -= w[i];

		// 3 �ܰ�
		// - ���� �Լ� ó��
		o = f( u );

		return o;
	}



	r2tm::TitleFunctionT LoadData::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "example : 4 - 1 : Load Data";
		};
	}
	r2tm::DoFunctionT LoadData::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			OUTPUT_NOTE( "������ �б�" );

			LS();

			DECLARATION_MAIN( double e[MAXINPUTNO][INPUTNO] ); // ������ ����

			LF();

			DECLARATION_MAIN( const int n_of_e = getdata( e ) );
			OUTPUT_VALUE( n_of_e );

			LF();

			PROCESS_MAIN( print_data( n_of_e, e ) );

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Do::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "example : 4 - 1 : Do";
		};
	}
	r2tm::DoFunctionT Do::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			OUTPUT_NOTE( "�ϳ��� �ΰ� �Ű� ���" );
			OUTPUT_NOTE( "������ ����ġ�� ���ΰ��� ���� �ΰ� �Ű��� �䳻 ��" );

			LF();

			OUTPUT_SUBJECT( "�۾� ����" );
			OUTPUT_COMMENT( "����ġ, ���ΰ� �ʱ�ȭ" );
			OUTPUT_COMMENT( "�Է� ������ �б�" );
			OUTPUT_COMMENT( "���" );
			OUTPUT_COMMENT( "   1. �Է°� �� ����ġ�� ���Ͽ� ��� ����" );
			OUTPUT_COMMENT( "   2. ���ΰ� ��" );
			OUTPUT_COMMENT( "   3. ���� �Լ��� �̿��Ͽ� ��°� ���" );

			LS();

			{
				DECLARATION_MAIN( double e[MAXINPUTNO][INPUTNO] );		// ������ ����
				DECLARATION_MAIN( const int n_of_e = getdata( e ) );	// ������ �б�
				OUTPUT_VALUE( n_of_e );

				LF();

				DECLARATION_MAIN( double w[INPUTNO + 1] );				// ����ġ�� ���ΰ�
				PROCESS_MAIN( init_w( w ) );							// ����ġ �ʱ�ȭ
				PROCESS_MAIN( print_w( w ) );

				LF();

				DECLARATION_MAIN( double o = 0 );						// ���

				SS();

				// ��� ��ü
				{
					for( int i = 0; n_of_e > i; ++i )
					{
						printf( "%2d", i );

						printf( "      input : " );
						for( int j = 0; INPUTNO > j; ++j )
						{
							printf( "%.2lf ", e[i][j] );
						}

						o = forward( w, e[i] );
						printf( "      output : %.2lf\n", o );
					}
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}