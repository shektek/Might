#include "RenderConsole.h"
#include "RenderConsoleColours.h"
#include <ncurses.h>

RenderConsole::RenderConsole(WINDOW *consoleWindow)
{
	_window = consoleWindow;
	_map = nullptr;
}

void RenderConsole::DrawMapCoordsBorder(BattleMap *map)
{
	for(int y = 0; y < map->GetHeight(); y++)
	{
        mvwaddch(_window, y+1, map->GetWidth()+2, y+'0');
	}

    for(int x = 0, xc = 0; x < map->GetWidth(); x++, xc += 1)
	{
		mvwaddch(_window, map->GetHeight()+2, xc+1, x +'A');
	}
}

void RenderConsole::DrawMap(BattleMap *map)
{
	_map = map;

	for(int y = 0; y < map->GetHeight(); y++)
	{
        for(int x = 0, xc = 0; x < map->GetWidth(); x++, xc+=1) //xc = x with spacing for console render only
		{
			char shape;
			int colour = 0;
			if(map->IsTileAccessible(x, y))
            {
                shape = GetTerrainShape(x, y);
                colour = GetTerrainColour(x, y);
			}
			else
			{
				shape = GetUnitShape(x, y);
				colour = GetUnitColour(x, y);
			}

			if (colour) wattron(_window, COLOR_PAIR(colour));
			mvwaddch(_window, y+1, xc+1, shape);
			if (colour) wattroff(_window, COLOR_PAIR(colour));
		}
	}
}

void RenderConsole::DrawMapHighlights(NavigableGrid submap)
{
    int mapHeight = submap.GetHeight();
    int mapWidth = submap.GetWidth();

    for(int y = 0; y < mapHeight; y++)
    {
        for(int x = 0; x < mapWidth; x++)
        {
            TileFloodNode *floodtile = submap.GetTile(x, y);
            OrdinalPosition loc = _map->GetArrayLocation(floodtile->tile->GlobalBottomLeft());

            char shape = '.';
            if(floodtile->tile->Occupied)
                shape = GetUnitShape(x, y);

            int colour = COLOUR_SELECTEDUNIT;
            if(floodtile->prev != nullptr)
                colour = COLOUR_DAMAGEDUNIT;
            if(floodtile->tile->Occupied && !floodtile->tile->Occupier->IsSelected)
                colour = GetUnitColour(x, y);

            wattron(_window, COLOR_PAIR(colour));
            mvwaddch(_window, loc.row +1, loc.column +1, shape);
            wattroff(_window, COLOR_PAIR(colour));
        }
    }
}

//create a submap at origin for radius squares in all directions
std::vector<std::vector<Tile*> > RenderConsole::GenerateRadialField(Point2D origin, int radius)
{
    std::vector<std::vector<Tile*> > result;
    result.resize(radius*2);

    //find the origin in the map
    //OrdinalPosition coords = _map->GetArrayLocation(origin);
    //turns out the origin is already an array index
    OrdinalPosition coords = {origin.x, origin.y};

    //from the given position, add an entry for each valid Tile
    for(int x = -radius, i = 0; x < radius; x++, i++)
    {
        if(coords.column + x < 0 || coords.column + x >= _map->GetWidth())
            continue;

        for(int y = -radius; y < radius; y++)
        {
            if(coords.row + y < 0 || coords.row + y >= _map->GetHeight())
                continue;

            result[i].push_back(_map->GetTile(coords.column+x, coords.row+y));
        }
    }

    std::vector<std::vector<Tile*> > actualresult;

    for(unsigned int i = 0; i < result.size(); i++)
    {
        if(result[i].size() > 0)
        {
            actualresult.push_back(result[i]);
        }
    }

    return actualresult;
}

//This will eventually get information about terrain from the Tile
char RenderConsole::GetTerrainShape(int x, int y)
{
	char result = '.';

	return result;
}

int RenderConsole::GetTerrainColour(int x, int y)
{
	int result = COLOUR_GRASSTERRAIN;

	return result;
}

//This will eventually get the type of unit and change the character
char RenderConsole::GetUnitShape(int x, int y)
{
	Unit *target = _map->GetUnitAt(x, y);

	char result = 'O';

    if(target != nullptr)
        result = target->Hitpoints <= 0 ? 'x' : result;

    return result;
}

int RenderConsole::GetUnitColour(int x, int y)
{
	Unit *target = _map->GetUnitAt(x, y);

	int result = 0;

    if(target != nullptr)
    {
        result = target->MaxHitpoints > target->Hitpoints ? COLOUR_DAMAGEDUNIT : result;
        result = target->IsSelected ? COLOUR_SELECTEDUNIT : result;
        result = target->Hitpoints <= 0 ? COLOUR_DEADUNIT : result;
    }

	return result;
}

void RenderConsole::DrawPlayerUnitInfo(Player *player, Unit *unit)
{
    mvwprintw(_window, 19, 1, "PLAYER %s    ", player->Name.c_str());
    mvwprintw(_window, 20, 1, "UNIT %s      ", unit->Name.c_str());
    mvwprintw(_window, 21, 1, "Speed: %d | Attack: %d    ", unit->Speed, unit->PrimaryAttack);
}
