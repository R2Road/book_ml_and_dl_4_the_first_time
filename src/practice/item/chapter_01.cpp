#include "chapter_01.hpp"

#include <conio.h>

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"

namespace chapter_01
{
	r2tm::TitleFunctionT _1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "practice : 1 - 1";
		};
	}
	r2tm::DoFunctionT _1::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			OUTPUT_NOTE( "합, 제곱 합 구하기" );
			OUTPUT_NOTE( "표준 입력에서 실수를 읽어" );
			OUTPUT_NOTE( "합과 제곱 합을 차례대로 출력 합니다." );

			LF();

			OUTPUT_SUBJECT( "[number] + [enter] Calculate" );
			OUTPUT_SUBJECT( "[q]      + [enter] End" );

			LS();

			{
				const int BUFFER_SIZE = 256;
				char linebuffer[BUFFER_SIZE];

				double result;
				double sum_normal = 0.f;
				double sum_pow2 = 0.f;

				while( fgets( linebuffer, BUFFER_SIZE, stdin ) )
				{
					//
					// [Q] : Exit
					//
					if( 'q' == linebuffer[0] && '\n' == linebuffer[1] )
					{
						break;
					}

					//
					// [Enter] : Skip
					//
					if( '\n' == linebuffer[0] )
					{
						printf( "[skip] : Input <Enter>" "\n\n" );
						continue;
					}

					if( sscanf_s( linebuffer, "%lf", &result ) )
					{
						//
						//
						//
						sum_normal += result;

						//
						//
						//
						sum_pow2 += ( result * result );

						//
						//
						//
						printf(
							"sum normal : %lf"
							"   "
							"sum pow2   : %lf"
							"\n"
							, sum_normal, sum_pow2
						);
					}
					else
					{
						printf(
							"[failed input]"
							" : "
							"%s"
							"\n"
							, linebuffer
						);
					}
				}
			}

			LS();

			return r2tm::eDoLeaveAction::None;
		};
	}
}