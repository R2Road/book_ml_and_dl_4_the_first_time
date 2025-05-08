#include "MenuExample03.hpp"

#include "r2tm/r2tm_Director.h"
#include "r2tm/r2tm_ostream.h"

#include "example/item/example_03_01.hpp"
#include "example/item/example_03_02.hpp"

#include "RootMenu.h"

r2tm::TitleFunctionT MenuExample03::GetTitleFunction() const
{
	return []()->const char*
	{
		return "chapter 3 군집지능과 진화연산 : 개미 무리 최적화, 진화 연산";
	};
}

r2tm::DescriptionFunctionT MenuExample03::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}

r2tm::WriteFunctionT MenuExample03::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* ret )
	{
		ret->AddMessage( "개미 무리 최적화", r2tm::eColor::FG_Green );
		ret->AddItem( '1', example_03_01::Do() );


		ret->AddLineFeed();
		ret->AddLineFeed();


		ret->AddMessage( "진화 연산", r2tm::eColor::FG_Green );
		ret->AddItem( 'q', example_03_02::Crossing() );
		ret->AddItem( 'w', example_03_02::Do() );



		ret->AddSplit();



		ret->AddMenu( 27, RootMenu() );
	};
}