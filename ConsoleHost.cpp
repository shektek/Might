#include "ConsoleHost.h"
#include "BattleMap.h"
#include "ArmyFactory.h"

ConsoleHost::ConsoleHost()
{
    _consoleWidth = 50;
    _consoleHeight = 25;
}

ConsoleHost::~ConsoleHost()
{

}

bool ConsoleHost::Init(int argc, char **argv)
{
    for(int i = 1; i < argc; i++)
    {
        if(strstr(argv[i], "-testArmies"))
            _testArmies = true;
        else if(strstr(argv[i], "-testPlayers"))
            _testPlayers = true;
        else if(strstr(argv[i], "-testMap"))
        {
            _mapWidth = 14;
            _mapHeight = 8;
        }
    }

    initscr();
    start_color();

    init_pair(COLOUR_SELECTEDUNIT, COLOR_BLUE, COLOR_BLACK);
    init_pair(COLOUR_DAMAGEDUNIT, COLOR_RED, COLOR_BLACK);
    init_pair(COLOUR_DEADUNIT, COLOR_BLACK, COLOR_RED);
    init_pair(COLOUR_GRASSTERRAIN, COLOR_BLACK, COLOR_GREEN);
    init_pair(COLOUR_DIRTTERRAIN, COLOR_BLACK, COLOR_YELLOW);

    _consoleWindow = newwin(_consoleHeight, _consoleWidth, 0, 0);
    box(_consoleWindow, 0, 0);

    _consoleRender = new RenderConsole(_consoleWindow);
    _consoleControl = new ControlConsole(_consoleWindow);

    _running = true;

    return _running;
}

void ConsoleHost::Exec(GameMaster *game)
{
    //begin the game
    _game = game;
    Army *leftarmy = nullptr;
    Army *rightarmy = nullptr;
    Player *leftplayer = nullptr;
    Player *rightplayer = nullptr;

    if(_testArmies)
    {
        leftarmy = ArmyFactory::CreateTestingArmy(6);
        rightarmy = ArmyFactory::CreateTestingArmy(6);
    }

    if(_testPlayers)
    {
        leftplayer = new Player("left player", leftarmy);
        rightplayer = new Player("right player", rightarmy);

        _game->AddPlayer(leftplayer);
        _game->AddPlayer(rightplayer);
    }

    BattleMap map(_mapWidth, _mapHeight, leftarmy, rightarmy);
    _game->PrepareRound(&map, AS_LEFT_DEFAULT, AS_RIGHT_DEFAULT);

    //battle loop
    while(_running)
    {
        _game->ApplySpellEffects();

        std::vector<Player*> player = _game->GetInitiativeOrder();

        for(int curPlayer = 0; curPlayer < 2; curPlayer++)
        {
            std::vector<Unit*> sortedUnits = player[curPlayer]->army->GetSpeedSorted();

            for(unsigned int i = 0; i < sortedUnits.size(); i++)
            {
                _game->SelectUnit(sortedUnits[i]);
                NavigableGrid submap = map.CreateFloodFillSubmap(sortedUnits[i]->Position, sortedUnits[i]->Speed);

                _consoleRender->DrawMap(&map);
                _consoleRender->DrawMapHighlights(&submap);
                _consoleRender->DrawMapCoordsBorder(&map);
                _consoleRender->DrawPlayerUnitInfo(player[curPlayer], sortedUnits[i]);
                mvwprintw(_consoleWindow, 23, 1, "Command > ");

                wrefresh(_consoleWindow);

                char cmd[256] = {0};
                wgetstr(_consoleWindow, cmd);
                wmove(_consoleWindow, 23, 1);

                for(int i = 1; i < _consoleWidth-2; i++)
                    mvwaddch(_consoleWindow, 23, i, ' ');

                _running = _consoleControl->ProcessCommand(&map, sortedUnits[i], cmd, submap);
            }
        }
    }

    _game->EndRound();
}

void ConsoleHost::Quit()
{
    delete _game;

    delwin(_consoleWindow);
    endwin();

    delete _consoleRender;
    delete _consoleControl;
}
