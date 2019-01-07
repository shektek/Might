#ifndef RENDER_CONSOLE_H
#define RENDER_CONSOLE_H

#include <cstdio>
#include <string>
#include <ncurses.h>
#include "Unit.h"
#include "BattleMap.h"
#include "Player.h"

//functions to render the map and units on it using the console
class RenderConsole
{
	private:
		WINDOW *_window;
		BattleMap *_map;

	        std::vector<std::vector<Tile*> > GenerateRadialField(Point2D origin, int radius);
		char GetTerrainShape(int x, int y);
		char GetUnitShape(int x, int y);
		int GetTerrainColour(int x, int y);
		int GetUnitColour(int x, int y);

	public:
		RenderConsole(WINDOW *consoleWindow);
		void DrawMap(BattleMap *map);
        	void DrawMapHighlights(NavigableGrid *submap);
		void DrawMapCoordsBorder(BattleMap *map);
		void DrawPlayerUnitInfo(Player *player, Unit *unit);
};

#endif
