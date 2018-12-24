#include "ConsoleHost.h"

int main(int argc, char **argv)
{
    srand((unsigned)time(0));

    AppHost *app = new ConsoleHost();

    if(app->Init(argc, argv))
        app->Exec();

    app->Quit();

    delete app;

	return 0;
}
