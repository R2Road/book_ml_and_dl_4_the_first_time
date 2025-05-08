#include "RootMenu.h"

#include <string>

#include "r2tm/r2tm_Director.h"
#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_VersionInfo.h"

#include "example/item/example_01_01.hpp"
#include "example/item/example_04_01.hpp"
#include "example/item/example_04_02.hpp"
#include "example/item/example_04_03.hpp"
#include "example/item/example_05_01.hpp"

#include "example/MenuExample02.hpp"
#include "example/MenuExample03.hpp"

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
		ret->AddMessage( "C ¿¹Á¦", r2tm::eColor::FG_Green );
		ret->AddItem( '1', example_01_01::Do() );


		ret->AddLineFeed();
		ret->AddLineFeed();


		ret->AddMenu( '2', MenuExample02() );

		ret->AddLineFeed();

		ret->AddMenu( '3', MenuExample03() );

		ret->AddLineFeed();

		ret->AddMessage( "ÀÎ°ø ½Å°æ¸Á 1", r2tm::eColor::FG_Green );
		ret->AddItem( 'a', example_04_01::LoadInputData() );
		ret->AddItem( 's', example_04_01::Do() );

		ret->AddMessage( "ÀÎ°ø ½Å°æ¸Á 2", r2tm::eColor::FG_Green );
		ret->AddItem( 'd', example_04_02::LoadInputData() );
		ret->AddItem( 'f', example_04_02::Do() );

		ret->AddMessage( "ÀÎ°ø ½Å°æ¸Á 3 : ¿ªÀüÆÄ", r2tm::eColor::FG_Green );
		ret->AddItem( 'g', example_04_03::LoadInputData() );
		ret->AddItem( 'h', example_04_03::Do() );



		ret->AddLineFeed();
		ret->AddLineFeed();



		ret->AddMessage( "µö·¯´× : ÇÕ¼º°ö ¿¬»ê", r2tm::eColor::FG_Green );
		ret->AddItem( 'z', example_05_01::LoadInputData() );
		ret->AddItem( 'x', example_05_01::Do() );



		ret->AddSplit();



		ret->AddExit( 27 );
	};
}