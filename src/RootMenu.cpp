#include "RootMenu.h"

#include <string>

#include "r2tm/r2tm_Director.h"
#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_VersionInfo.h"

#include "example/item/example_01_01.hpp"
#include "example/item/example_02_02.hpp"
#include "example/item/example_02_03.hpp"
#include "example/item/example_03_01.hpp"
#include "example/item/example_03_02.hpp"

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
		ret->AddItem( '1', example_01_01::Do() );
		ret->AddItem( '2', example_02_02::LoadData() );
		ret->AddItem( '3', example_02_02::Do() );
		ret->AddItem( '4', example_02_03::Do() );
		ret->AddItem( '5', example_03_01::Do() );
		ret->AddItem( '6', example_03_02::Crossing() );
		ret->AddItem( '7', example_03_02::Do() );



		ret->AddSplit();



		ret->AddExit( 27 );
	};
}