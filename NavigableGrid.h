#ifndef NAVIGABLE_GRID_H
#define NAVIGABLE_GRID_H

#include <cmath>
#include "Army.h"
#include "Unit.h"
#include "Tile.h"
#include "OrdinalPosition.h"

//used to construct a backwards-flowing network of tiles for pathfinding
//inheritance/composition? Inheriting from Tile might be better
struct TileFloodNode
{
    bool mapped;
    Tile *tile; //pointer to the tile data
    TileFloodNode *prev; //the tile leading to this one
};

/* A navigable grid is a submap of a BattleMap including all blocked tiles.
 * Generally this is for movement of units but could also be useful for other
 * effects, such as a chain lightning spell which must navigate between units
 */
class NavigableGrid
{
	private:
		Tile *_origin;
        std::vector<std::vector<TileFloodNode*> > _map;
        int _width;
        int _height;

	public:
		NavigableGrid();
        NavigableGrid(Tile *origin, std::vector<std::vector<TileFloodNode*> > map);
		NavigableGrid(const NavigableGrid &other);
		NavigableGrid &operator=(const NavigableGrid &other);
		~NavigableGrid();

        inline int GetWidth() {if(_width == -1) _width = _map.size(); return _width;}
        inline int GetHeight() {if(_height == -1) if(_map.size() > 0) _height = _map[0].size(); return _height;}

        TileFloodNode *GetTile(int column, int row);
};

#endif
