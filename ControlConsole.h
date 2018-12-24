#ifndef CONTROL_CONSOLE_H
#define CONTROL_CONSOLE_H

#include "Unit.h"
#include "BattleMap.h"
#include "NavigableGrid.h"
#include <cstdio>
#include <cstring>
#include <ncurses.h>

//control state by console commands
class ControlConsole
{
	private:
		WINDOW *_window;
		Unit *_lastControlledUnit;

	public:
		ControlConsole(WINDOW *controlConsole);
        bool ProcessCommand(BattleMap *map, Unit *unit, char *cmd, NavigableGrid movementSubmap);
};

#endif
