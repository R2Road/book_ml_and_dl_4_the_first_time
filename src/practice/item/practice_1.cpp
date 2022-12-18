#include "practice_1.h"

#include <conio.h> // _getch

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

			std::cout << r2cm::tab2 << "Do Something" << r2cm::linefeed;

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}