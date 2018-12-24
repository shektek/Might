#ifndef UNIT_H
#define UNIT_H

#include "Point2D.h"
#include <string>

class Unit
{
	private:

	public:
		//public properties are temporary
		bool IsSelected;
		short MaxHitpoints;
		short Hitpoints;
		short Speed;
		short PrimaryAttack; //this needs to be an array of structs containing damage type, amount, range, and any extra effects
		short SecondaryAttack; //as above
		std::string Name;
		Point2D Position;

		Unit();
		Unit(const Unit &other);
		Unit(std::string name);

		~Unit();

		Unit &operator=(const Unit &other);

		short GetSpeedRating();
		short GetMeleeRating();
		short GetRangeRating();

		void AttackUnit(Unit *other);
};

#endif
