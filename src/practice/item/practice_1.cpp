#include "practice_1.h"

#include <conio.h>

#include "r2cm/r2cm_ostream.h"

namespace practice_1
{
	r2cm::iItem::TitleFunctionT _1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "practice : 1 - 1";
		};
	}
	r2cm::iItem::DoFunctionT _1::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

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

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::None;
		};
	}
}