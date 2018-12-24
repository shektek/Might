#include "ConsoleHost.h"

ConsoleHost::ConsoleHost()
{
    _consoleWidth = 50;
    _consoleHeight = 25;
}

bool ConsoleHost::Init()
{
    initscr();
    start_color();

    init_pair(COLOUR_SELECTEDUNIT, COLOR_BLUE, COLOR_BLACK);
    init_pair(COLOUR_DAMAGEDUNIT, COLOR_RED, COLOR_BLACK);
    init_pair(COLOUR_DEADUNIT, COLOR_BLACK, COLOR_RED);
    init_pair(COLOUR_GRASSTERRAIN, COLOR_BLACK, COLOR_GREEN);
    init_pair(COLOUR_DIRTTERRAIN, COLOR_BLACK, COLOR_YELLOW);

    _consoleWindow = newwin(_consoleHeight, _consoleWidth, 0, 0);
    box(consoleWindow, 0, 0);

    _consoleRenderer = new RenderConsole(_consoleWindow);
    _consoleControl = ControlConsole(_consoleWindow);

    _running = true;
}

void ConsoleHost::Exec()
{
    while(_running)
    {
        game.ApplySpellEffects();

        std::vector<Player*> player = game.GetInitiativeOrder();

        for(int curPlayer = 0; curPlayer < 2; curPlayer++)
        {
            std::vector<Unit*> sortedUnits = player[curPlayer]->army->GetSpeedSorted();

            for(unsigned int i = 0; i < sortedUnits.size(); i++)
            {
                game.SelectUnit(sortedUnits[i]);
                NavigableGrid submap = map.CreateFloodFillSubmap(sortedUnits[i]->Position, sortedUnits[i]->Speed);

                _consoleRenderer.DrawMap(&map);
                _consoleRenderer.DrawMapHighlights(submap);
                _consoleRenderer.DrawMapCoordsBorder(&map);
                _consoleRenderer.DrawPlayerUnitInfo(player[curPlayer], sortedUnits[i]);
                mvwprintw(_consoleWindow, 23, 1, "Command > ");

                wrefresh(_consoleWindow);

                char cmd[256] = {0};
                wgetstr(_consoleWindow, cmd);
                wmove(_consoleWindow, 23, 1);

                for(int i = 1; i < _consoleWidth-2; i++)
                    mvwaddch(_consoleWindow, 23, i, ' ');

                _running = _consoleControl.ProcessCommand(&map, sortedUnits[i], cmd, submap);
            }
        }
    }
}

void ConsoleHost::Quit()
{
    delwin(consoleWindow);
    endwin();
}
