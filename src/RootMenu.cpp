#include "RootMenu.h"

#include <string>

#include "r2tm/r2tm_Director.h"
#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_VersionInfo.h"

#include "example/item/example_01_01.hpp"
#include "example/item/example_03_01.hpp"
#include "example/item/example_03_02.hpp"
#include "example/item/example_04_01.hpp"
#include "example/item/example_04_02.hpp"
#include "example/item/example_04_03.hpp"
#include "example/item/example_05_01.hpp"

#include "example/MenuExample02.hpp"

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
		return "    " "책 : 처음 만나는 머신러닝과 딥러닝";
	};
}

r2tm::WriteFunctionT RootMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* ret )
	{
		ret->AddMessage( "C 예제", r2tm::eColor::FG_Green );
		ret->AddItem( '1', example_01_01::Do() );


		ret->AddLineFeed();
		ret->AddLineFeed();


		ret->AddMenu( '2', MenuExample02() );



		ret->AddLineFeed();
		ret->AddLineFeed();



		ret->AddMessage( "개미 무리 최적화", r2tm::eColor::FG_Green );
		ret->AddItem( 'q', example_03_01::Do() );

		ret->AddMessage( "진화 연산", r2tm::eColor::FG_Green );
		ret->AddItem( 'w', example_03_02::Crossing() );
		ret->AddItem( 'e', example_03_02::Do() );



		ret->AddLineFeed();
		ret->AddLineFeed();



		ret->AddMessage( "인공 신경망 1", r2tm::eColor::FG_Green );
		ret->AddItem( 'a', example_04_01::LoadInputData() );
		ret->AddItem( 's', example_04_01::Do() );

		ret->AddMessage( "인공 신경망 2", r2tm::eColor::FG_Green );
		ret->AddItem( 'd', example_04_02::LoadInputData() );
		ret->AddItem( 'f', example_04_02::Do() );

		ret->AddMessage( "인공 신경망 3 : 역전파", r2tm::eColor::FG_Green );
		ret->AddItem( 'g', example_04_03::LoadInputData() );
		ret->AddItem( 'h', example_04_03::Do() );



		ret->AddLineFeed();
		ret->AddLineFeed();



		ret->AddMessage( "딥러닝 : 합성곱 연산", r2tm::eColor::FG_Green );
		ret->AddItem( 'z', example_05_01::LoadInputData() );
		ret->AddItem( 'x', example_05_01::Do() );



		ret->AddSplit();



		ret->AddExit( 27 );
	};
}