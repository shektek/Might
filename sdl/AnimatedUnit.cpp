#include "AnimatedUnit.h"

AnimatedUnit::AnimatedUnit() : Unit()
{
	_classType = U_ANIMATED;
	_current = nullptr;
}

AnimatedUnit::AnimatedUnit(const Unit &other)
{
	_classType = U_ANIMATED;
	_selected = other.IsSelected();
	_maxHitpoints = other.GetMaxHitpoints();
	_hitpoints = other.GetHitpoints();
	_speed = other.GetSpeed();
	_remainingMovement = other.GetRemainingMovement();
	_primaryAttack = other.GetPrimaryAttack();
	_secondaryAttack = other.GetSecondaryAttack();
	_name = other.GetName();
	_position = other.GetPosition();

	if(other.GetType() == U_ANIMATED)
	{
		_idle = ((AnimatedUnit)other).GetIdleAnimationSet();
		_move = ((AnimatedUnit)other).GetMoveAnimationSet();
		_attack = ((AnimatedUnit)other).GetAttackAnimationSet();
		_die = ((AnimatedUnit)other).GetDieAnimationSet();
		_current = ((AnimatedUnit)other).GetCurrentAnimation();
	}
}

AnimatedUnit::AnimatedUnit(short maxHp, short spd, short prmAtk, short scdAtk, std::string nm, Point2D pos, std::string portraitFilename, AnimatedImage idleSet, AnimatedImage mvSet, AnimatedImage atkSet, AnimatedImage dieSet)
	: Unit(maxHp, spd, prmAtk, scdAtk, nm, pos, portraitFilename)
{
	_classType = U_ANIMATED;
	_idle = idleSet;
	_move = mvSet;
	_attack = atkSet;
	_die = dieSet;
	_current = &_idle;
}

AnimatedUnit::~AnimatedUnit()
{
	//should delete the animation sets?
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
