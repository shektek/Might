#include "Tile.h"

Tile::Tile()
{
	Occupied = false;
	Occupier = nullptr;
	_width = 0;
	_height = 0;
	_position = Point2D();
}

Tile::Tile(const Tile &other)
{
	Occupied = other.Occupied;
	Occupier = other.Occupier;
	_width = other._width;
	_height = other._height;
	_position = other._position;
}

Tile::Tile(Point2D blCorner, short width, short height)
{
	Occupied = false;
	Occupier = nullptr;
	_width = width;
	_height = height;
	_position = blCorner;
}

Tile::~Tile()
{
}

Tile &Tile::operator=(const Tile &other)
{
	Occupied = other.Occupied;
	Occupier = other.Occupier;
	_width = other._width;
	_height = other._height;
	_position = other._position;
	return *this;
}

bool Tile::ContainsPoint(Point2D position)
{
    Point2D gtr = GlobalTopRight();
    Point2D gbl = GlobalBottomLeft();

    return ((position.x < gtr.x && position.y < gtr.y) &&
            (position.x >= gbl.x && position.y >= gbl.y));
}

Point2D Tile::LocalBottomLeft()
{
	return Point2D(0, 0);
}

Point2D Tile::LocalTopLeft()
{
	return Point2D(0, _width);
}

Point2D Tile::LocalTopRight()
{
	return Point2D(_height, _width);
}

Point2D Tile::LocalBottomRight()
{
	return Point2D(_width, 0);
}

Point2D Tile::LocalCentre()
{
	return Point2D(_width / 2, _height / 2);
}

Point2D Tile::GlobalBottomLeft()
{
	return _position;
}

Point2D Tile::GlobalTopLeft()
{
	return Point2D(_width, _height + _position.y);
}

Point2D Tile::GlobalTopRight()
{
	return Point2D(_width + _position.x, _height + _position.y);
}

Point2D Tile::GlobalBottomRight()
{
	return Point2D(_width + _position.x, _height);
}

Point2D Tile::GlobalCentre()
{
	return Point2D(_width / 2 + _position.x, _height / 2 + _position.y);
}

