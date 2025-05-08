#include "MenuExample04.hpp"

#include "r2tm/r2tm_Director.h"
#include "r2tm/r2tm_ostream.h"

#include "example/item/example_04_01.hpp"
#include "example/item/example_04_02.hpp"
#include "example/item/example_04_03.hpp"

#include "RootMenu.h"

r2tm::TitleFunctionT MenuExample04::GetTitleFunction() const
{
	return []()->const char*
	{
		return "chapter 4 �Ű�� : �ΰ� �Ű��, ������";
	};
}

r2tm::DescriptionFunctionT MenuExample04::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}

r2tm::WriteFunctionT MenuExample04::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* ret )
	{
		ret->AddMessage( "�ΰ� �Ű�� 1", r2tm::eColor::FG_Green );
		ret->AddItem( 'a', example_04_01::LoadInputData() );
		ret->AddItem( 's', example_04_01::Do() );


		ret->AddLineFeed();
		ret->AddLineFeed();


		ret->AddMessage( "�ΰ� �Ű�� 2", r2tm::eColor::FG_Green );
		ret->AddItem( 'd', example_04_02::LoadInputData() );
		ret->AddItem( 'f', example_04_02::Do() );


		ret->AddLineFeed();
		ret->AddLineFeed();


		ret->AddMessage( "�ΰ� �Ű�� 3 : ������", r2tm::eColor::FG_Green );
		ret->AddItem( 'g', example_04_03::LoadInputData() );
		ret->AddItem( 'h', example_04_03::Do() );



		ret->AddSplit();



		ret->AddMenu( 27, RootMenu() );
	};
}