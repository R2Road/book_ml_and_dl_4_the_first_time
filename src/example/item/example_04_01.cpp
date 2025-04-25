#include "example_04_01.hpp"

#include <cstdio>
#include <cstdlib>
#include <conio.h>

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "utility4example.hpp"

namespace example_04_01
{
	const int INPUTNO = 2;			// �Է� ����
	const int MAXINPUTNO = 100;		// �������� �ִ� ����



	// ���� �Լ�
	double f( double u )
	{
		return 0;
	}
	// ����ġ�� ���ΰ� �ʱ�ȭ
	void init_w( double w[INPUTNO + 1] )
	{
	}

	// ������ ���
	double forward( double w[INPUTNO + 1] )
	{
		return 0;
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
			std::cout << r2tm::split;

			OUTPUT_NOTE( "�ϳ��� �ΰ� �Ű� ���" );
			OUTPUT_NOTE( "������ ����ġ�� ���ΰ��� ���� �ΰ� �Ű��� �䳻 ��" );

			LS();

			DECLARATION_MAIN( double e[MAXINPUTNO][INPUTNO] );		// ������ ����
			DECLARATION_MAIN( const int n_of_e = getdata( e ) );	// ������ �б�

			DECLARATION_MAIN( double w[INPUTNO + 1] );				// ����ġ�� ���ΰ�
			PROCESS_MAIN( init_w( w ) );
			
			LS();

			{
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}