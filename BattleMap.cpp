
#include "BattleMap.h"

BattleMap::BattleMap()
{
	_height = 0;
	_width = 0;
	_leftArmy = nullptr;
	_rightArmy = nullptr;
}

BattleMap::BattleMap(short width, short height)
    : BattleMap(width, height, 1, 1)
{
}

BattleMap::BattleMap(short width, short height, short tileWidth, short tileHeight)
    : BattleMap()
{
    _width = width;
    _height = height;
    _map.resize(_width);
    for(int i = 0; i < _width; i++)
    {
        _map[i].resize(_height);
    }

    for(int y = height-1; y >= 0; y--)
    {
        for(int x = 0; x < width; x++)
        {
            _map[x][y] = Tile(Point2D(x*tileWidth, y*tileHeight), tileWidth, tileHeight);
            //_map[x][y].SetPosition(x, y);
        }
    }
}

BattleMap::BattleMap(short width, short height, Army *leftArmy, Army *rightArmy)
    : BattleMap(width, height, 1, 1, leftArmy, rightArmy)
{
}

BattleMap::BattleMap(short width, short height, short tileWidth, short tileHeight, Army *leftArmy, Army *rightArmy)
    : BattleMap(width, height, tileWidth, tileHeight)
{
    _leftArmy = leftArmy;
    _rightArmy = rightArmy;
}

BattleMap::BattleMap(std::vector<std::vector<Tile> > map, Army *leftArmy, Army *rightArmy)
{
	_map = map;
	_width = _map.size();
	_height = _map[0].size();
    _leftArmy = leftArmy;
    _rightArmy = rightArmy;
}

BattleMap::BattleMap(const BattleMap &other)
{
	_height = other._height;
	_width = other._width;
	_map = other._map;
	_leftArmy = other._leftArmy;
	_rightArmy = other._rightArmy;
}

BattleMap &BattleMap::operator=(const BattleMap &other)
{
	_height = other._height;
	_width = other._width;
	_map = other._map;
	_leftArmy = other._leftArmy;
	_rightArmy = other._rightArmy;
	return *this;
}

OrdinalPosition GetFloodArrayLocation(std::vector<std::vector<TileFloodNode*> > array, Point2D position)
{
    OrdinalPosition result;
    result.column = result.row = -1;

    for(unsigned int i = 0; i < array.size(); i++)
    {
        for(unsigned int j = 0; j < array[i].size(); j++)
        {
            if(array[i][j]->tile->ContainsPoint(position))
            {
                result.column = i;
                result.row = j;
                return result;
            }
        }
    }

    return result;
}

NavigableGrid BattleMap::CreateFloodFillSubmap(Point2D position, short radius)
{
    Tile *origin = GetContainingTile(position);
    OrdinalPosition originPos = GetArrayLocation(position);
    std::vector<std::vector<TileFloodNode*> > submap;
    std::vector<OrdinalPosition> kill;

    submap.resize(radius*2+1);
    for(short i = 0; i < radius*2+1; i++)
    {
        submap[i].resize(radius*2+1);
        for(short j = 0; j < radius*2+1; j++)
        {
            short pos_i = originPos.column + i - radius;
            short pos_j = originPos.row + j - radius;

            //get the tile from the battlemap
            Tile *thisTile = GetTile(pos_i, pos_j);

            if(thisTile)
            {
                submap[i][j] = new TileFloodNode();
                submap[i][j]->mapped = false;
                submap[i][j]->prev = nullptr;
                submap[i][j]->tile = thisTile;
            }
            else
            {
                kill.push_back(OrdinalPosition{i, j});
            }
        }
    }

    //erase empty columns
    int last_i = 0;
    for(unsigned int i = 0, j = 0; i < kill.size(); i++, j++)
    {
        int this_i = kill[i].column;

        if(last_i != this_i)
            j = 0;
        last_i = this_i;

        int this_j = kill[i].row - j;
        delete submap[this_i][this_j];
        submap[this_i].erase(submap[this_i].begin() + this_j);
    }

    //erase empty rows
    unsigned int nonEmpty = 0;
    while(nonEmpty < submap.size())
    {
        if(submap[nonEmpty].size() == 0)
            submap.erase(submap.begin() + nonEmpty);
        else
            nonEmpty++;
    }

    if(origin != nullptr)
    {
        _currentSubmap = submap;
        FloodFill(origin, radius, nullptr);
    }

    return NavigableGrid(origin, submap);
}

void BattleMap::FloodFill(Tile *currentOrigin, short remainingRadius, TileFloodNode *prev)
{
    //first ensure this exists in the battlemap
    OrdinalPosition origin = GetFloodArrayLocation(_currentSubmap, currentOrigin->GlobalBottomLeft());

    if(origin.column != -1 && origin.row != -1)
    {
        _currentSubmap[origin.column][origin.row]->tile = currentOrigin;
        _currentSubmap[origin.column][origin.row]->mapped = true;
        _currentSubmap[origin.column][origin.row]->prev = prev;

        //columns
        //-1 0 1
        //-1 0 1
        //-1 0 1
        //rows
        // 1  1  1
        // 0  0  0
        //-1 -1 -1

        if(remainingRadius > 0)
        {
		auto Fill = [this](unsigned int thisColumn, unsigned int thisRow, int remainingRadius)
		{
			if(thisColumn >= 0 && thisRow >= 0 &&
			    thisColumn < this->_currentSubmap.size() && thisRow < this->_currentSubmap[thisColumn].size() &&
			    this->_currentSubmap[thisColumn][thisRow]->mapped == false &&
			    this->_currentSubmap[thisColumn][thisRow]->tile->Occupied == false)
				FloodFill(this->_currentSubmap[thisColumn][thisRow]->tile, remainingRadius-1, this->_currentSubmap[thisColumn][thisRow]);
		};

		Fill(origin.column+1, origin.row, remainingRadius);
		Fill(origin.column-1, origin.row, remainingRadius);

		Fill(origin.column+1, origin.row+1, remainingRadius);
		Fill(origin.column+1, origin.row-1, remainingRadius);

		Fill(origin.column, origin.row+1, remainingRadius);
		Fill(origin.column, origin.row-1, remainingRadius);

		Fill(origin.column-1, origin.row+1, remainingRadius);
		Fill(origin.column-1, origin.row-1, remainingRadius);

/*
            for(int i = -1; i < 2; i++)
            {
                for(int j = -1; j < 2; j++)
                {
                    if(//!(i == 0 && j == 0) &&  //don't try to remap the origin
                        origin.column + i > 0 && origin.column + i < _currentSubmap.size() &&   //don't go outside map bounds
                        origin.row + j > 0 && origin.row + j < _currentSubmap[origin.column + i].size() &&
                        _currentSubmap[origin.column+i][origin.row+j]->mapped == false)  //don't remap if already mapped
                    {
                        TileFloodNode *tmpLastOrigin = _currentSubmap[origin.column][origin.row];
                        FloodFill(_currentSubmap, _currentSubmap[origin.column+i][origin.row+j]->tile, --remainingRadius, tmpLastOrigin);
                    }
                }
            }
*/
        }
    }
}

void BattleMap::FloodFill(std::vector<std::vector<TileFloodNode*> > &submap, Tile *currentOrigin, short remainingRadius, TileFloodNode *lastOrigin)
{
    --remainingRadius;

    //first ensure this exists in the battlemap
    OrdinalPosition origin = GetFloodArrayLocation(submap, currentOrigin->GlobalBottomLeft());

    if(origin.column != -1 && origin.row != -1)
    {
        submap[origin.column][origin.row]->tile = currentOrigin;
        submap[origin.column][origin.row]->mapped = true;
        submap[origin.column][origin.row]->prev = lastOrigin;

        //columns
        //-1 0 1
        //-1 0 1
        //-1 0 1
        //rows
        // 1  1  1
        // 0  0  0
        //-1 -1 -1

        if(remainingRadius > 0)
        {
            for(unsigned int i = -1; i < 2; i++)
            {
                for(unsigned int j = -1; j < 2; j++)
                {
                    if(i != 0 && j != 0 &&  //don't try to remap the origin
                        origin.column + i > 0 && origin.column + i < submap.size() &&   //don't go outside map bounds
                        origin.row + j > 0 && origin.row + j < submap[origin.column + i].size() &&
                        submap[origin.column+i][origin.row+j]->mapped == false)  //don't remap if already mapped
                    {
                        TileFloodNode *tmpLastOrigin = submap[origin.column][origin.row];
                        FloodFill(submap, submap[origin.column+i][origin.row+j]->tile, remainingRadius, tmpLastOrigin);
                    }
                }
            }
        }
    }
}

void BattleMap::ArrangeUnits(Army *targetArmy, ArrangementStrategy strategy)
{
	switch(strategy)
	{
		case AS_RIGHT_DEFAULT:
			ArrangeUnitsDefault(targetArmy, _width-1);
		break;

		case AS_LEFT_DEFAULT:
		default:
			ArrangeUnitsDefault(targetArmy, 0);
		break;
	}
}

void BattleMap::ArrangeUnitsDefault(Army *targetArmy, short column)
{
	int direction = column >= _width/2 ? -1 : 1;

	for(int i = 0, j = 0; i < targetArmy->GetUnitCount(); i++, j++)
	{
		if(j >= _height)
		{
			column += direction;
			j = 0;
		}

		if(!_map[column][j].Occupied)
		{
			auto pos = _map[column][j].GlobalBottomLeft();
			targetArmy->GetUnitAt(i)->Position = pos;
			_map[column][j].Occupied = true;
			_map[column][j].Occupier = targetArmy->GetUnitAt(i);
		}
	}
}

bool BattleMap::IsTileAccessible(short column, short row)
{
	bool result = false;

	if(column < _width && row < _height)
	{
		result = !_map[column][row].Occupied;
	}

	return result;
}

bool BattleMap::IsTileAccessible(Point2D position)
{
    //Get position as array indices
    OrdinalPosition pos = GetArrayLocation(position);

    if(pos.column != -1 && pos.row != -1)
        return IsTileAccessible(pos.column, pos.row);

    return false;
}

Unit *BattleMap::GetUnitAt(short column, short row)
{
	Unit *found = nullptr;

	if(!IsTileAccessible(column, row))
	{
		found =  _map[column][row].Occupier;
	}

	return found;
}

Army *BattleMap::GetOwningArmy(Unit *unit)
{
	Army *army = nullptr;

	if(_leftArmy->FindUnit(unit))
		army = _leftArmy;
	else if(_rightArmy->FindUnit(unit))
		army = _rightArmy;

	return army;
}

//if this ends up being too slow use a binary search
Tile *BattleMap::GetContainingTile(Point2D position)
{
    for(unsigned int i = 0; i < _map.size(); i++)
    {
        for(unsigned int j = 0; j < _map[i].size(); j++)
        {
            if(_map[i][j].ContainsPoint(position))
            {
                return &_map[i][j];
            }
        }
    }

    return nullptr;
}

OrdinalPosition BattleMap::GetArrayLocation(Point2D position)
{
	OrdinalPosition result;
	result.column = result.row = -1;

	for(unsigned int i = 0; i < _map.size(); i++)
	{
		for(unsigned int j = 0; j < _map[i].size(); j++)
		{
			if(_map[i][j].ContainsPoint(position))
			{
                		result.column = i;
                		result.row = j;
                		return result;
			}
		}
	}

	return result;
}

Tile *BattleMap::GetTile(short column, short row)
{
    Tile *result = nullptr;

    if(column >= 0 && column < GetWidth() && row >= 0 && row < GetHeight())
        result = &_map[column][row];

    return result;
}

void BattleMap::RemoveUnitPiece(Unit *unit)
{
    if(unit != nullptr)
    {
        _map[unit->Position.x][unit->Position.y].Occupied = false;
        _map[unit->Position.x][unit->Position.y].Occupier = nullptr;
    }
}

void BattleMap::MoveUnitToPosition(Unit *unit, short column, short row)
{
	if(unit != nullptr && IsTileAccessible(column, row))
	{
		short oldx = unit->Position.x;
		short oldy = unit->Position.y;

		OrdinalPosition oldPos = GetArrayLocation(Point2D(oldx, oldy));

		if(oldPos.column != column || oldPos.row != row)
		{
			_map[oldPos.column][oldPos.row].Occupied = false;
			_map[oldPos.column][oldPos.row].Occupier = nullptr;
			unit->Position = _map[column][row].GlobalBottomLeft();
			_map[column][row].Occupied = true;
			_map[column][row].Occupier = unit;
		}
	}
}

void BattleMap::MoveUnitToPosition(Unit *unit, Point2D position)
{
	if(unit != nullptr)
	{
		OrdinalPosition pos = GetArrayLocation(position);

		if(pos.column != -1 && pos.row != -1)
			MoveUnitToPosition(unit, pos.column, pos.row);
	}
}


void BattleMap::RescaleTiles(short newWidth, short newHeight)
{
	for(int i = 0; i < _width; i++)
	{
		for(int j = 0; j < _height; j++)
		{
			_map[i][j].SetSize(newWidth, newHeight);
			_map[i][j].SetPosition(i * newWidth, j * newHeight);
			if(_map[i][j].Occupier != nullptr)
				_map[i][j].Occupier->Position = _map[i][j].GlobalBottomLeft();
		}
	}
}
