#include "GameMaster.h"

GameMaster::GameMaster()
{
	_left = nullptr;
	_right = nullptr;
	_current = nullptr;
	_leftArmy = nullptr;
	_rightArmy = nullptr;
	_previousSelected = nullptr;
	_currentSelected = nullptr;
}

GameMaster::GameMaster(Player *left, Player *right)
{
	_left = left;
	_right = right;
	_current = nullptr;
	_leftArmy = _left->army;
	_rightArmy = _right->army;
	_previousSelected = nullptr;
	_currentSelected = nullptr;
}

bool GameMaster::AddPlayer(Player *newPlayer)
{
	if(_left == nullptr)
	{
        	_left = newPlayer;
		_leftArmy = _left->army;
	}
	else if(_right == nullptr)
	{
	        _right = newPlayer;
		_rightArmy = _right->army;
	}
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

	auto arrangedPlayers = GetInitiativeOrder();
	_current = arrangedPlayers[0];
	SelectUnit(_current->army->GetUnitAt(0));
}

void GameMaster::PrepareRound(BattleMap *map, Army *left, Army *right, ArrangementStrategy leftArrangement, ArrangementStrategy rightArrangement)
{
	_map = map;
	_leftArmy = left;
	_rightArmy = right;

	_map->ArrangeUnits(_leftArmy, leftArrangement);
	_map->ArrangeUnits(_rightArmy, rightArrangement);

	auto arrangedPlayers = GetInitiativeOrder();
	_current = arrangedPlayers[0];
	SelectUnit(_current->army->GetUnitAt(0));
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

void GameMaster::StepRound()
{
	ApplySpellEffects();

	//get the next piece to move, switching players if necessary
	if(_currentSelected == _current->army->GetUnitAt(_current->army->GetUnitCount()-1))
	{
		if(_current == _left)
			_current = _right;
		else
			_current = _left;

		SelectUnit(_current->army->GetUnitAt(0));
	}
	else
	{
		for(int i = 0; i < _current->army->GetUnitCount(); i++)
			if(_current->army->GetUnitAt(i) == _currentSelected)
			{
				SelectUnit(_current->army->GetUnitAt(i+1));
				break;
			}
	}
}

void GameMaster::EndRound()
{

}
