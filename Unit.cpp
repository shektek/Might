#include "Unit.h"

Unit::Unit()
{
	_classType = U_BASE;
	_selected = false;
	_maxHitpoints = _hitpoints = 0;
	_speed = 0;
	_remainingMovement = 0;
	_primaryAttack = 0;
	_secondaryAttack = 0;
	_name = "None";
	_position = Point2D(0,0);
	_portraitFilename = "";
}

Unit::Unit(std::string name) : Unit()
{
	_name = name;
}

Unit::Unit(const Unit &other)
{
	_classType = other._classType;
	_selected = other._selected;
	_maxHitpoints = other._maxHitpoints;
	_hitpoints = other._hitpoints;
	_speed = other._speed;
	_remainingMovement = other._remainingMovement;
	_primaryAttack = other._primaryAttack;
	_secondaryAttack = other._secondaryAttack;
	_position = other._position;
	_name = other._name;
	_portraitFilename = other._portraitFilename;
}

Unit::Unit(short maxHitpoints, short speed, short primaryAttack, short secondaryAttack, std::string name, Point2D startPosition, std::string portraitFilename)
{
	_classType = U_BASE;
	_selected = false;
	_hitpoints = _maxHitpoints = maxHitpoints;
	_remainingMovement = _speed = speed;
	_primaryAttack = primaryAttack;
	_secondaryAttack = secondaryAttack;
	_name = name;
	_position = startPosition;
	_portraitFilename = portraitFilename;
}

Unit::~Unit()
{
}

Unit &Unit::operator=(const Unit &other)
{
	_classType = other._classType;
	_selected = other._selected;
	_maxHitpoints = other._maxHitpoints;
	_hitpoints = other._hitpoints;
	_speed = other._speed;
	_remainingMovement = other._remainingMovement;
	_primaryAttack = other._primaryAttack;
	_secondaryAttack = other._secondaryAttack;
	_position = other._position;
	_name = other._name;
	_portraitFilename = other._portraitFilename;
	return *this;
}

//Apply damage to this unit's hitpoints and return any excess damage
short Unit::ApplyDamage(short damagePoints)
{
	short remainder = 0;
	if(_hitpoints > 0)
	{
		_hitpoints -= damagePoints;

		if(_hitpoints < 0)
		{
			remainder = damagePoints - _hitpoints;
			_hitpoints = 0;
		}
	}
	else remainder = damagePoints;

	return remainder;
}

short Unit::HealHitpoints(short healPoints)
{
	short remainder = 0;
	if(_hitpoints < _maxHitpoints && _hitpoints > 0)
	{
		_hitpoints += healPoints;

		if(_hitpoints > _maxHitpoints)
		{
			remainder = _hitpoints - _maxHitpoints;
			_hitpoints = _maxHitpoints;
		}
	}
	else remainder = healPoints;

	return remainder;
}

//consider putting some checks around this and returning a success state
void Unit::Move(Point2D newPosition, short steps)
{
	_position = newPosition;
	_remainingMovement -= steps;
}

//all of the following are incomplete!
short Unit::GetSpeedRating()
{
	return _speed;
}

short Unit::GetMeleeRating()
{
	return _primaryAttack + _secondaryAttack;
}

short Unit::GetRangeRating()
{
	return _secondaryAttack;
}

short Unit::AttackUnit(Unit *other)
{
	return other->ApplyDamage(_primaryAttack);
}

void Unit::TurnReset()
{
	if(!IsDead())
		_remainingMovement = _speed;
}

void Unit::FullReset()
{
	_remainingMovement = _speed;
	_hitpoints = _maxHitpoints;
}

void Unit::Resurrect()
{
	_hitpoints = _maxHitpoints;
}
