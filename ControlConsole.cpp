#include "ControlConsole.h"
#include "NavigableGrid.h"

ControlConsole::ControlConsole(WINDOW *consoleWindow)
{
	_window = consoleWindow;
	_lastControlledUnit = nullptr;
}

//TODO: make this return an enum with the command result (e.g. quit, out of range, etc.)
//      add entries into an action solver to take the command and process it while rendering
bool ControlConsole::ProcessCommand(BattleMap *map, Unit *selectedUnit, char *cmd, NavigableGrid movementSubmap)
{
	bool keepRunning = true;
	char ctx;
	int tX, tY;

	if(strstr(cmd, "quit"))
		keepRunning = false;
	else if(sscanf(cmd, "move %c %d", &ctx, &tY) == 2)
	{
		tX = ctx - 'A';

		if(tX >= 0 && tX < map->GetWidth() && tY >= 0 && tY < map->GetHeight())
		{
            std::vector<Tile*> occupied;
            for(int i = 0; i < map->GetWidth(); i++)
            {
                for(int j = 0; j < map->GetHeight(); j++)
                {
                    Tile *here = map->GetTile(i, j);
                    if(here->Occupied)
                        occupied.push_back(here);
                }
            }

            Tile *unitStart = map->GetTile(selectedUnit->Position.x, selectedUnit->Position.y);
            Tile *unitEnd = map->GetTile(tX, tY);



            //disabled as right now it actually doesn't matter anyway - no obstacles
            /*
            NavigableGrid route(&unitStart, map->GetRawArray(), occupied);

            micropather::MPVector<void*> path;
            float cost;

            int solved = route.Solve(&unitStart, &unitEnd, &path, &cost);

            //actually needs to move along the path
            if(solved == micropather::MicroPather::SOLVED && cost <= selectedUnit->Speed)
                map->MoveUnitToPosition(selectedUnit, tX, tY);
            */

            /* TODO:
             * - move this to it's own class
             * - use a floodfill to determine accessible squares & create a navigable grid
             * - use A* to determine the actual path to the goal
             */
            //first, is the target square accessible?
            if(map->IsTileAccessible(tX, tY))
            {
                //check that euclidean distance to the node is within unit speed
                double dx = unitStart->GlobalBottomLeft().x - unitEnd->GlobalBottomLeft().x;
                double dy = unitStart->GlobalBottomLeft().y - unitEnd->GlobalBottomLeft().y;
                double distance = sqrt((dx*dx) + (dy*dy));

                if (distance <= selectedUnit->Speed)
                {
                    map->MoveUnitToPosition(selectedUnit, tX, tY);
                }
            }
		}
	}
	else if(sscanf(cmd, "attack %c %d", &ctx, &tY) == 2)
	{
		tX = ctx - 'A';
		if(tX >= 0 && tX < map->GetWidth() && tY >= 0 && tY < map->GetHeight())
		{
			Unit *heAttac = selectedUnit;
			Unit *heProtec = map->GetUnitAt(tX, tY);

			heAttac->AttackUnit(heProtec);
			//TODO: this actually needs to be handled elsewhere
			if(heProtec->Hitpoints <= 0)
			{
				Army *army = map->GetOwningArmy(heProtec);
				if(army != nullptr)
				{
                    //this behaviour could change
					map->RemoveUnitPiece(heProtec);
					army->RemoveUnit(heProtec);
				}
			}
		}
	}

	return keepRunning;
}
