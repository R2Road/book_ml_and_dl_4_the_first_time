#include "MenuExample01.hpp"

#include "r2tm/r2tm_Director.h"
#include "r2tm/r2tm_ostream.h"

#include "example/item/example_01_01.hpp"

#include "RootMenu.h"

r2tm::TitleFunctionT MenuExample01::GetTitleFunction() const
{
	return []()->const char*
	{
		return "chapter 1 �ӽŷ����̶�? : C����";
	};
}

r2tm::DescriptionFunctionT MenuExample01::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}

r2tm::WriteFunctionT MenuExample01::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* ret )
	{
		ret->AddMessage( "C ����", r2tm::eColor::FG_Green );
		ret->AddItem( '1', example_01_01::Do() );



		ret->AddSplit();



		ret->AddMenu( 27, RootMenu() );
	};
}