#include "RootMenu.h"

#include <string>

#include "r2tm/r2tm_Director.h"
#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_VersionInfo.h"

#include "practice/item/chapter_01.hpp"
#include "practice/item/chapter_02_02.hpp"
#include "practice/item/chapter_02_03.hpp"
#include "practice/item/chapter_03_01.hpp"

r2tm::TitleFunctionT RootMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		static const std::string ret =
			std::string()

			+ "Root Menu"
			" : "	"<"   "C++17" + ">"
			", "	"<"   "MS C/C++ : " + std::to_string( _MSC_VER ) + ">"
			", "	"<" + r2tm::VersionInfo.String4Version + ">"
			;
		return ret.c_str();
	};
}

r2tm::DescriptionFunctionT RootMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "    " "Ã¥ : Ã³À½ ¸¸³ª´Â ¸Ó½Å·¯´×°ú µö·¯´×";
	};
}

r2tm::WriteFunctionT RootMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* ret )
	{
		ret->AddItem( '1', chapter_01::_1() );
		ret->AddItem( '2', chapter_02_02::Example() );
		ret->AddItem( '3', chapter_02_03::Example() );
		ret->AddItem( '4', chapter_03_01::Example() );



		ret->AddSplit();



		ret->AddExit( 27 );
	};
}