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
        GameMaster *_game;

        //debug stuff
        bool _testPlayers;
        bool _testArmies;
        bool _testMap;
        int _mapWidth;
        int _mapHeight;

    public:
        ConsoleHost();
        virtual ~ConsoleHost();

        bool Init(int argc, char **argv);
        void Exec(GameMaster *game);
        void Quit();
};

#endif // CONSOLEHOST_H
