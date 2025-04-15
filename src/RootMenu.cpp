#include "RootMenu.h"

#include <string>

#include "r2tm/r2tm_Director.h"
#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_VersionInfo.h"

#include "practice/item/practice_01.h"

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
		ret->AddItem( '1', practice_01::_1() );



		ret->AddSplit();



		ret->AddExit( 27 );
	};
}