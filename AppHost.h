#ifndef APPHOST_H
#define APPHOST_H

#include "GameMaster.h"

class AppHost
{
    public:
        virtual ~AppHost() {}

        //initialise the application host (create windows, consoles, controllers, etc.)
        virtual bool Init(int argc, char **argv) = 0;

        //the application main loop, initialise game-specific objects (players, armies, etc.) and run the game
        virtual void Exec(GameMaster *game) = 0;

        //delete windows, consoles, controllers, etc.
        virtual void Quit() = 0;
};

#endif
