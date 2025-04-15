#include "practice_01.h"

#include <conio.h>

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"

namespace practice_01
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
			std::cout << r2tm::split;

			OUTPUT_SUBJECT( "[number] + [enter] Calculate" );
			OUTPUT_SUBJECT( "[q]      + [enter] End" );

			std::cout << r2tm::split;

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

			std::cout << r2tm::split;

			return r2tm::eDoLeaveAction::None;
		};
	}
}