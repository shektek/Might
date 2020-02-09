//#define CONSOLE_MIGHT
#ifdef CONSOLE_MIGHT
	#include "ConsoleHost.h"
	#define HOST_TYPE ConsoleHost
#else
	#include "sdl/SDLHost.h"
	#define HOST_TYPE SDLHost
#endif

#include <ctime>

int main(int argc, char **argv)
{
    srand((unsigned)time(0));

    AppHost *app = new HOST_TYPE();

    if(app->Init(argc, argv))
        app->Exec(new GameMaster());

    app->Quit();

    delete app;

	return 0;
}
