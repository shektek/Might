#include "GameMaster.h"

GameMaster::GameMaster()
{
    _left = nullptr;
    _right = nullptr;
    _previousSelected = nullptr;
    _currentSelected = nullptr;
}

GameMaster::GameMaster(Player *left, Player *right)
{
	_left = left;
	_right = right;
	_previousSelected = nullptr;
	_currentSelected = nullptr;
}

bool GameMaster::AddPlayer(Player *newPlayer)
{
    if(_left == nullptr)
        _left = newPlayer;
    else if(_right == nullptr)
        _right = newPlayer;
    else return false;

    return true;
}

void GameMaster::PrepareRound(BattleMap *map, ArrangementStrategy leftArrangement, ArrangementStrategy rightArrangement)
{
    _map = map;
    if(_left != nullptr)
        _leftArmy = _left->army;
    if(_right != nullptr)
        _rightArmy = _right->army;

    _map->ArrangeUnits(_leftArmy, leftArrangement);
    _map->ArrangeUnits(_rightArmy, rightArrangement);
}

void GameMaster::PrepareRound(BattleMap *map, Army *left, Army *right, ArrangementStrategy leftArrangement, ArrangementStrategy rightArrangement)
{
	_map = map;
	_leftArmy = left;
	_rightArmy = right;

	_map->ArrangeUnits(_leftArmy, leftArrangement);
	_map->ArrangeUnits(_rightArmy, rightArrangement);
}

void GameMaster::ApplySpellEffects()
{
	//look for area-of-effect spells and any units inside
	//look for units with residual effects
}

std::vector<Player*> GameMaster::GetInitiativeOrder()
{
	std::vector<Player*> ret;
	std::vector<Unit*> firstSpeed = _leftArmy->GetSpeedSorted();
	std::vector<Unit*> secondSpeed = _rightArmy->GetSpeedSorted();

	if(secondSpeed[0]->GetSpeedRating() > firstSpeed[0]->GetSpeedRating())
	{
		ret.push_back(_right);
		ret.push_back(_left);
	}
	else
	{
		ret.push_back(_left);
		ret.push_back(_right);
	}

	return ret;
}

void GameMaster::SelectUnit(Unit *unit)
{
	if(_currentSelected != nullptr)
		_currentSelected->IsSelected = false;
	_previousSelected = _currentSelected;
	unit->IsSelected = true;
	_currentSelected = unit;
}

void GameMaster::EndRound()
{

}
