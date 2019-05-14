#ifndef ANIMATEDUNIT_H
#define ANIMATEDUNIT_H

#include "../Unit.h"
#include "AnimatedImage.h"

enum AnimationState
{
	AS_IDLE,
	AS_MOVE,
	AS_ATTACK,
	AS_DIE
};

class AnimatedUnit : public Unit
{
	protected:
		AnimatedImage	_idle;
		AnimatedImage	_move;
		AnimatedImage	_attack;
		AnimatedImage	_die;

		AnimatedImage	*_current;

	public:
		AnimatedUnit();
		AnimatedUnit(const Unit &other);
		AnimatedUnit(short maxHp, short spd, short prmAtk, short scdAtk, std::string nm, Point2D pos, AnimatedImage idleSet, AnimatedImage moveSet, AnimatedImage attackSet, AnimatedImage dieSet);

		~AnimatedUnit();

		AnimatedUnit 	&operator=(const Unit &other);

		AnimatedImage	*GetCurrentAnimation() { return _current; }
		AnimatedImage	GetIdleAnimationSet() { return _idle; }
		AnimatedImage	GetMoveAnimationSet() { return _move; }
		AnimatedImage	GetAttackAnimationSet() { return _attack; }
		AnimatedImage	GetDieAnimationSet() { return _die; }

		void		SetCurrentAnimation(AnimationState animState);
		void		SetIdleAnimationSet(AnimatedImage newIdleSet) { _idle = newIdleSet; }
		void		SetMoveAnimationSet(AnimatedImage newMoveSet) { _move = newMoveSet; }
		void		SetAttackAnimationSet(AnimatedImage newAttackSet) { _attack = newAttackSet; }
		void		SetDieAnimationSet(AnimatedImage newDieSet) { _die = newDieSet; }
};

#endif
