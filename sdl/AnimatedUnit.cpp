#include "AnimtedUnit.h"

AnimatedUnit::AnimatedUnit() : Unit()
{
	_classType = U_ANIMATED;
	_current = nullptr;
}

AnimatedUnit::AnimatedUnit(const Unit &other)
{
	_classType = U_ANIMATED;
	_selected = other._selected;
	_maxHitpoints = other._maxHitpoints;
	_hitpoints = other._hitpoints;
	_speed = other._speed;
	_remainingMovement = other._remainingMovement;
	_primaryAttack = other._primaryAttack;
	_secondaryAttack = other._secondaryAttack;
	_name = other._name;
	_position = other._position;

	if(other._classType == U_ANIMATED)
	{
		_idle = ((AnimatedUnit)other)._idle;
		_move = ((AnimatedUnit)other)._move;
		_attack = ((AnimatedUnit)other)._attack;
		_die = ((AnimatedUnit)other)._die;
		_current = ((AnimatedUnit)other)._current;
	}
}

AnimatedUnit::AnimatedUnit(short maxHp, short spd, short prmAtk, short scdAtk, std::string nm, Point2D pos, AnimatedImage idleSet, AnimatedImage mvSet, AnimatedImage atkSet, AnimatedImage dieSet)
	: Unit(maxHp, spd, prmAtk, scdAtk, nm, pos)
{
	_classType = U_ANIMATED;
	_idle = idleSet;
	_move = mvSet;
	_attack = atkSet;
	_die = dieSet;
	_current = &_idle;
}

AnimatedUnit::~AnimatedUnit() : ~Unit()
{
}

void AnimatedUnit::SetCurrentAnimation(AnimationState animState)
{
	switch(animState)
	{
		case AS_IDLE:
			_current = &_idle;
			break;

		case AS_MOVE:
			_current = &_move;
			break;

		case AS_ATTACK:
			_current = &_attack;
			break;

		case AS_DIE:
			_current = &_die;
			break;

		default:
			_current = &_idle;
	}
}
