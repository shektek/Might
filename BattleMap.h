#ifndef BATTLEMAP_H
#define BATTLEMAP_H

#include <vector>
#include "Point2D.h"
#include "Tile.h"
#include "Army.h"
#include "ArrangementStrategy.h"
#include "NavigableGrid.h"
#include "OrdinalPosition.h"

/* A BattleMap represents the space on which two armies face off.
 * The BattleMap class provides the map of Tiles, pointers to the two armies,
 * and functions to check whether a Tile is accessible, navigate between Tiles,
 * etc.
 * For now it's just basic, but in future should be extended to allow for army
 * starting positions, a way to add obstacles and weight pathfinding e.g. for
 * area of effect spells. It may need to be templated to different tile types
 * if I decide to use a hex grid over squares.
 */
class BattleMap
{
	private:
		std::vector<std::vector<Tile> > _map;
        	std::vector<std::vector<TileFloodNode*> > _currentSubmap;
		short _height;
		short _width;
		Army* _leftArmy;
		Army* _rightArmy;

		void ArrangeUnitsDefault(Army *targetArmy, short column);
        	void FloodFill(std::vector<std::vector<TileFloodNode*> > &submap, Tile *currentOrigin, short remainingRadius, TileFloodNode *lastOrigin);
        	void FloodFill(Tile *currentOrigin, short remainingRadius, TileFloodNode *prev);

	public:
		BattleMap();
		BattleMap(short width, short height);
        	BattleMap(short width, short height, short tileWidth, short tileHeight);
		BattleMap(short width, short height, Army *leftArmy, Army *rightArmy);
	        BattleMap(short width, short height, short tileWidth, short tileHeight, Army *leftArmy, Army *rightArmy);
		BattleMap(std::vector<std::vector<Tile> > map, Army *leftArmy, Army *rightArmy);
		BattleMap(const BattleMap &other);
		BattleMap &operator=(const BattleMap &other);

	        //Create a navigable grid at a position with a radius
        	NavigableGrid CreateFloodFillSubmap(Point2D position, short radius);

		//Arrange units according to an arrangement strategy
		void ArrangeUnits(Army *targetArmy, ArrangementStrategy strategy);

		//Checks whether a tile has an entry point from any direction
		bool IsTileAccessible(short column, short row);
		bool IsTileAccessible(Point2D position);

		void RemoveUnitPiece(Unit *unit);
		Unit *GetUnitAt(short column, short row);
		Army *GetOwningArmy(Unit *unit);
        	Tile *GetContainingTile(Point2D position);
        	OrdinalPosition GetArrayLocation(Point2D position);
        	Tile *GetTile(short column, short row);

		//Moves a unit to an x,y coordinate
		void MoveUnitToPosition(Unit *unit, short column, short row);
		void MoveUnitToPosition(Unit *unit, Point2D position);

        	inline std::vector<std::vector<Tile> > GetRawArray() const { return _map; }
		inline short GetHeight() const { return _height; }
		inline short GetWidth() const { return _width; }

        	//Resize the tiles and adjust their position
        	void RescaleTiles(short newWidth, short newHeight);
};

#endif
