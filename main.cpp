#ifdef CONSOLE_MIGHT
    #include "ConsoleHost.h"
#else
    #include "QtHost.h"
#endif

int main(int argc, char **argv)
{
    srand((unsigned)time(0));

    AppHost *app = new QtHost();

    if(app->Init(argc, argv))
        app->Exec();

    app->Quit();

    delete app;

	return 0;
}
