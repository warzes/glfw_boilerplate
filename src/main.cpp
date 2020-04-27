#include "Framework.h"
#include "App.h"
//-----------------------------------------------------------------------------
int main()
{
	try
	{
		Window window(800, 600, "Hello", true, true);
		App app;
		while ( !window.IsEnd() )
		{
			app.Update();
			app.Draw();
			window.Swap();
		}
	}
	catch ( const std::exception &exp )
	{
		std::cout << "ERROR: " << exp.what() << std::endl;
	}
}
//-----------------------------------------------------------------------------