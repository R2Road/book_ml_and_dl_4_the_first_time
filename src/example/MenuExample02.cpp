#include "MenuExample02.hpp"

#include "r2tm/r2tm_Director.h"
#include "r2tm/r2tm_ostream.h"

#include "example/item/example_02_02.hpp"
#include "example/item/example_02_03.hpp"

#include "RootMenu.h"

r2tm::TitleFunctionT MenuExample02::GetTitleFunction() const
{
	return []()->const char*
	{
		return "chapter 2 ¸Ó½Å·¯´×ÀÇ ±âÃÊ : ±Í³³ ÇÐ½À, °­È­ ÇÐ½À";
	};
}

r2tm::DescriptionFunctionT MenuExample02::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}

r2tm::WriteFunctionT MenuExample02::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* ret )
	{
		ret->AddMessage( "±Í³³ ÇÐ½À", r2tm::eColor::FG_Green );
		ret->AddItem( '1', example_02_02::LoadData() );
		ret->AddItem( '2', example_02_02::Do() );


		ret->AddLineFeed();
		ret->AddLineFeed();


		ret->AddMessage( "°­È­ ÇÐ½À", r2tm::eColor::FG_Green );
		ret->AddItem( 'q', example_02_03::Do() );



		ret->AddSplit();



		ret->AddMenu( 27, RootMenu() );
	};
}