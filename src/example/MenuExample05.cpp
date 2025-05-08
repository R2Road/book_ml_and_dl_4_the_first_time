#include "MenuExample05.hpp"

#include "r2tm/r2tm_Director.h"
#include "r2tm/r2tm_ostream.h"

#include "example/item/example_05_01.hpp"

#include "RootMenu.h"

r2tm::TitleFunctionT MenuExample05::GetTitleFunction() const
{
	return []()->const char*
	{
		return "chapter 5 µö·¯´× : ÇÕ¼º°ö ¿¬»ê, ÀÚ±â ºÎÈ£È­±â";
	};
}

r2tm::DescriptionFunctionT MenuExample05::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}

r2tm::WriteFunctionT MenuExample05::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* ret )
	{

		ret->AddMessage( "µö·¯´× : ÇÕ¼º°ö ¿¬»ê", r2tm::eColor::FG_Green );
		ret->AddItem( 'z', example_05_01::LoadInputData() );
		ret->AddItem( 'x', example_05_01::Do() );



		ret->AddSplit();



		ret->AddMenu( 27, RootMenu() );
	};
}