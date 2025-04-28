#include "example_04_02.hpp"

#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <math.h> // exp

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "utility4example.hpp"

namespace example_04_02
{
	const int INPUTNO = 2;			// �Է� ����
	const int HIDDENNO = 2;			// �߰����� �� ����
	const int MAXINPUTNO = 100;		// �������� �ִ� ����



	// �߰����� ����ġ�� �ʱ�ȭ
	void init_wh( double wh[HIDDENNO][INPUTNO + 1] )
	{
		wh[0][0] = -2;
		wh[0][1] = 3;
		wh[0][2] = -1;
		wh[1][0] = -2;
		wh[1][1] = 1;
		wh[1][2] = 0.5;
		
	}
	void print_wh( double wh[HIDDENNO][INPUTNO + 1] )
	{
		for( int i = 0; HIDDENNO > i; ++i )
		{
			printf( "    " );
			for( int j = 0; INPUTNO + 1 > j; ++j )
			{
				printf( "%.2f  ", wh[i][j] );
			}
			printf( "\n" );
		}
	}

	// ������� ����ġ�� �ʱ�ȭ
	void init_wo( double wo[HIDDENNO + 1] )
	{
		wo[0] = -60;
		wo[1] = 94;
		wo[2] = -1;
	}
	void print_wo( double wo[HIDDENNO + 1] )
	{
		printf( "    " );
		for( int i = 0; HIDDENNO + 1 > i; ++i )
		{
			printf( "%.2f  ", wo[i] );
		}
		printf( "\n" );
	}

	// ������ �б�
	int load_input( double e[][INPUTNO] )
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
	void print_input( const int count, double e[][INPUTNO] )
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
	double forward(
		  double wh[HIDDENNO][INPUTNO + 1]
		, double wo[HIDDENNO + 1]
		, double hi[]
		, double e[INPUTNO]
	)
	{
		double u = 0; // �߰��� ��갪
		double o = 0; // ����� ��갪

		//
		// �߰��� ���
		// 
		int i = 0;
		int j = 0;
		for( i = 0; HIDDENNO > i; ++i )
		{
			u = 0;
			for( j = 0; INPUTNO > j; ++j )
			{
				// 1 �ܰ�
				// - ������ �Է¿� ����ġ�� ���Ѵ�.
				// - �� ����� ��� ���Ѵ�.
				u += e[j] * wh[i][j];
			}

			// 2 �ܰ�
			// - ���ΰ� ó��
			//
			// �˾ƺ��� ����� �̵����� �ڵ带 ¥�� �ϳ�?
			u -= wh[i][j];

			// 3 �ܰ�
			// - �߰��� ��� �� ����
			hi[i] = f( u );
		}

		//
		// ����� ���
		//
		o = 0;
		for( i = 0; HIDDENNO > i; ++i )
		{
			// 1 �ܰ�
			// - ������ �Է¿� ����ġ�� ���Ѵ�.
			// - �� ����� ��� ���Ѵ�.
			o += hi[i] * wo[i];
		}
		// 2 �ܰ�
		// - ���ΰ� ó��
		//
		// �˾ƺ��� ����� �̵����� �ڵ带 ¥�� �ϳ�?
		o -= wo[i];

		return f( o );
	}



	r2tm::TitleFunctionT LoadInputData::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "example : 4 - 2 : Load Input Data";
		};
	}
	r2tm::DoFunctionT LoadInputData::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			OUTPUT_NOTE( "������ �б�" );

			LS();

			DECLARATION_MAIN( double e[MAXINPUTNO][INPUTNO] ); // ������ ����

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
			return "example : 4 - 2 : Do";
		};
	}
	r2tm::DoFunctionT Do::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			OUTPUT_NOTE( "�ܼ��� ������ �Ű�� ���" );
			OUTPUT_NOTE( "��¸��� ���( �н� ���� )" );

			LF();

			OUTPUT_SUBJECT( "�Ű�� ����" );
			OUTPUT_COMMENT( "2���� �Է� -> 2���� �߰��� -> 1���� �����" );

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
				DECLARATION_MAIN( const int n_of_e = load_input( e ) );	// ������ �б�
				OUTPUT_VALUE( n_of_e );
				PROCESS_MAIN( print_input( n_of_e, e ) );

				LF();

				DECLARATION_MAIN( double wh[HIDDENNO][INPUTNO + 1] );	// �߰��� ����ġ�� ���ΰ�
				PROCESS_MAIN( init_wh( wh ) );							// ����ġ �ʱ�ȭ
				PROCESS_MAIN( print_wh( wh ) );

				LF();

				DECLARATION_MAIN( double wo[INPUTNO + 1] );				// ����� ����ġ�� ���ΰ�
				PROCESS_MAIN( init_wo( wo ) );							// ����ġ �ʱ�ȭ
				PROCESS_MAIN( print_wo( wo ) );

				LF();

				DECLARATION_MAIN( double hi[INPUTNO + 1] );				// �߰��� ���
				DECLARATION_MAIN( double o = 0 );						// ����� ���

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

						o = forward( wh, wo, hi, e[i] );
						printf( "      output : %.2lf\n", o );
					}
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}