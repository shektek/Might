#ifndef UNIT_H
#define UNIT_H

#include "UnitClassTypes.h"
#include "Point2D.h"
#include <string>

class Unit
{
	protected:
		UnitClassType _classType;
		bool _selected;
		short _maxHitpoints;
		short _hitpoints;
		short _speed;
		short _remainingMovement;
		short _primaryAttack; //this needs to be an array of structs containing damage type, amount, range, and any extra effects
		short _secondaryAttack; //as above
		std::string _name;
		Point2D _position;
		std::string _portraitFilename;

	public:
		Unit();
		Unit(const Unit &other);
		Unit(std::string name);
		Unit(short maxHitpoints, short speed, short primaryAttack, short secondaryAttack, std::string name, Point2D startPosition, std::string portraitFilename);

		virtual ~Unit();

		Unit &operator=(const Unit &other);

		bool IsSelected() { return _selected; }
		bool IsDead() { return _hitpoints == 0; }
		short GetMaxHitpoints() { return _maxHitpoints; }
		short GetHitpoints() { return _hitpoints; }
		short GetSpeed() { return _speed; }
		short GetRemainingMovement() { return _remainingMovement; }
		short GetPrimaryAttack() { return _primaryAttack; }
		short GetSecondaryAttack() { return _secondaryAttack; }
		std::string GetName() { return _name; }
		Point2D GetPosition() { return _position; }
		std::string GetPortraitFilename() { return _portraitFilename; }

		void Select() { _selected = true; }
		void Deselect() { _selected = false; }
		void SetMaxHitpoints(short newMax) { _maxHitpoints = newMax; }
		short ApplyDamage(short damagePoints);
		short HealHitpoints(short healPoints);
		void SetHitpoints(short newHitpoints) { _hitpoints = newHitpoints; }
		void SetSpeed(short newSpeed) { _speed = newSpeed; }
		void SetRemainingMovement(short newRemnant) { _remainingMovement = newRemnant; }
		void SetPrimaryAttack(short newPrimary) { _primaryAttack = newPrimary; }
		void SetSecondaryAttack(short newSecondary) { _secondaryAttack = newSecondary; }
		void SetName(std::string newName) { _name = newName; }
		void SetPosition(Point2D newPosition) { _position = newPosition; }
		void SetPortraitFilename(std::string portraitFilename) { _portraitFilename = portraitFilename; }
		void Move(Point2D newPosition, short steps);

		short GetSpeedRating();
		short GetMeleeRating();
		short GetRangeRating();

		short AttackUnit(Unit *other);
		void TurnReset();
		void FullReset();
		void Resurrect();
};

#endif
