#include "RootMenu.h"

#include <string>

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"
#include "r2cm/r2cm_VersionInfo.h"

#include "practice/item/practice_1.h"

const char* RootMenu::GetTitle()
{
	static const std::string ret =
		std::string( "Root Menu" )
		+ " : <" + r2cm::VersionInfo.String4Version + ">";
	return ret.c_str();
}

r2cm::MenuUp RootMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddItem( '1', empty_test::Basic() );



		ret->AddSplit();



		ret->AddItem(
			27
			, []()->const char* { return "Exit"; }
			, []()->r2cm::eItemLeaveAction { return r2cm::eItemLeaveAction::Exit; }
		);
	}

	return ret;
}