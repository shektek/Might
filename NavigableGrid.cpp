#include "NavigableGrid.h"

NavigableGrid::NavigableGrid()
{
    _origin = nullptr;
    _width = -1;
    _height = -1;
}

NavigableGrid::NavigableGrid(Tile *origin, std::vector<std::vector<TileFloodNode*> > map)
{
    _origin = origin;
    _map = map;
    _width = map.size();
    _height = map[0].size();
}

NavigableGrid::NavigableGrid(const NavigableGrid &other)
{
	_origin = other._origin;
    _map = other._map;
    _width = other._width;
    _height = other._height;
}

NavigableGrid &NavigableGrid::operator=(const NavigableGrid &other)
{
	_origin = other._origin;
    _map = other._map;
    _width = other._width;
    _height = other._height;
	return *this;
}

NavigableGrid::~NavigableGrid()
{
}

TileFloodNode *NavigableGrid::GetTile(int column, int row)
{
    TileFloodNode *result = nullptr;

    if(column >= 0 && column < _width && row >= 0 && row < _height)
        result = _map[column][row];

    return result;
}

