#ifndef TILE_H
#define TILE_H

#include "Unit.h"
#include "Point2D.h"

/* Basic square tile.
 * Provides functions to get the various corners of the tile and the centre, both
 * in it's local coordinates and in the global (map) coordinates
 */
class Tile
{
	private:
		//size of the tile
		short _width;
		short _height;
		//position of the bottom left corner
		Point2D _position;
	public:
		bool Occupied;
		Unit *Occupier; //this is a pure pointer. No deep copy necessary

		Tile();
		Tile(const Tile &other);
		Tile(Point2D blCorner, short width, short height);
		~Tile();

		Tile &operator=(const Tile &other);

		//Sets the position by bottom left corner
		inline void SetPosition(short x, short y) { _position.x = x; _position.y = y; }

		inline short GetWidth() const { return _width; }
		inline short GetHeight() const { return _height; }

        bool ContainsPoint(Point2D position);

		//Functions to get the local coords of the tile (0...width, 0...height)
		Point2D LocalBottomLeft();
		Point2D LocalTopLeft();
		Point2D LocalTopRight();
		Point2D LocalBottomRight();
		Point2D LocalCentre();

		//Functions to the the mapwise coords of the tile
		Point2D GlobalBottomLeft();
		Point2D GlobalTopLeft();
		Point2D GlobalTopRight();
		Point2D GlobalBottomRight();
		Point2D GlobalCentre();
};

#endif
