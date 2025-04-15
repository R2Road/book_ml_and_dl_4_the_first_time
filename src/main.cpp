#if defined( DEBUG ) || defined( _DEBUG )
	#include "vld/include/vld.h"
#endif

#include "r2tm/r2tm_Director.h"
#include "r2tm/r2tm_WindowsUtility.h"
#include "RootMenu.h"

int main()
{
	//
	// Environment : Title
	//
	r2tm::WindowsUtility::ChangeTitle( "ml_and_dl_4_the_first_time" );

	//
	// Environment : Size
	//
	r2tm::WindowsUtility::Resize( 960, 960 );

	//
	// Environment : Position
	//
	r2tm::WindowsUtility::Move( 0, 0 );

	//
	// Setup
	//
	r2tm::Director director;
	director.Setup( RootMenu() );

	//
	// Environment : ScrollBar | Maximize Button | Frame Lock | QuickEdit
	//
	r2tm::WindowsUtility::ScrollBarVisible( false );
	r2tm::WindowsUtility::MaximizeButtonEnable( false );
	r2tm::WindowsUtility::ResizingByDraggingEnable( false );
	r2tm::WindowsUtility::QuickEditEnable( false );

	//
	// Process
	//
	director.Run();

	return 0;
}
