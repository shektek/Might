#include <algorithm>
#include "Army.h"

Army::Army()
{
}

Army::Army(const Army &other)
{
	_units = other._units;
}

Army::~Army()
{
    for(unsigned int i = 0; i < _units.size(); i++)
	{
		delete _units[i];
		_units[i] = nullptr;
	}
	_units.clear();
}

Army &Army::operator=(const Army &other)
{
	_units = other._units;

    return *this;
}

Unit *Army::GetUnitAt(int index)
{
	Unit *result = nullptr;

    if((unsigned int)index < _units.size())
	{
		result = _units[index];
	}

	return result;
}

void Army::RemoveUnit(Unit *unit)
{
    for(unsigned int i = 0; i < _units.size(); i++)
	{
		if(_units[i]->GetName() == unit->GetName() && _units[i]->GetPosition().x == unit->GetPosition().x && _units[i]->GetPosition().y == unit->GetPosition().y)
		{
			delete _units[i];
			_units.erase(_units.begin() + i);
			unit = nullptr;
			break;
		}
	}
}

void Army::AddUnit(Unit *unit)
{
	_units.push_back(unit);
}

bool Army::FindUnit(Unit *unit)
{
	bool found = false;

	for(unsigned int i = 0; i < _units.size(); i++)
	{
		if(_units[i]->GetName() == unit->GetName() && _units[i]->GetPosition().x == unit->GetPosition().x && _units[i]->GetPosition().y == unit->GetPosition().y)
		{
			found = true;
			break;
		}
	}

	return found;
}

void Army::DeselectAll()
{
	for(Unit *unit : _units)
		unit->Deselect();
}

void Army::SelectUnit(Unit *unit)
{
	for(unsigned int i = 0; i < _units.size(); i++)
	{
		if(_units[i]->GetName() == unit->GetName() && _units[i]->GetPosition().x == unit->GetPosition().x && _units[i]->GetPosition().y == unit->GetPosition().y)
		{
			_units[i]->Select();
		}
	}
}

//Prioritise by unit speed - whoever moves farthest + 0.5 * secondary movement
//Some units have the ability to move after attacking, but this is considered less important
std::vector<Unit*> Army::GetSpeedSorted()
{
	std::vector<Unit*> sorted = _units;

	std::sort(sorted.begin(), sorted.end(), [](Unit *a, Unit *b) -> bool
		{ return a->GetSpeedRating() > b->GetSpeedRating(); });

	return sorted;
}

//Prioritise by all melee attacks (primary or secondary)
std::vector<Unit*> Army::GetMeleeSorted()
{
	std::vector<Unit*> sorted = _units;

	std::sort(sorted.begin(), sorted.end(), [](Unit *a, Unit *b) -> bool
		{ return a->GetMeleeRating() > b->GetMeleeRating(); });

	return sorted;
}

//Prioritise by all ranged attacks (primary or secondary) including any magical attacks
std::vector<Unit*> Army::GetRangeSorted()
{
	std::vector<Unit*> sorted = _units;

	std::sort(sorted.begin(), sorted.end(), [](Unit *a, Unit *b) -> bool
		{ return a->GetRangeRating() > b->GetRangeRating(); });

	return sorted;
}
