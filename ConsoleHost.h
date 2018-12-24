#ifndef CONSOLEHOST_H
#define CONSOLEHOST_H

#include <ncurses.h>
#include "GameMaster.h"
#include "AppHost.h"
#include "RenderConsole.h"
#include "RenderConsoleColours.h"
#include "ControlConsole.h"


class ConsoleHost : public AppHost
{
    private:
        WINDOW *_consoleWindow;
        int _consoleWidth;
        int _consoleHeight;
        RenderConsole *_consoleRender;
        ControlConsole *_consoleControl;
        bool _running;

    public:
        ConsoleHost();

        bool Init();
        void Exec();
        void Quit();
};

#endif // CONSOLEHOST_H
