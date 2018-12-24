#include "Unit.h"

Unit::Unit()
{
	IsSelected = false;
	MaxHitpoints = Hitpoints = 0;
	Speed = 0;
	PrimaryAttack = 0;
	SecondaryAttack = 0;
	Name = "None";
}

Unit::Unit(const Unit &other)
{
	IsSelected = other.IsSelected;
	MaxHitpoints = other.MaxHitpoints;
	Hitpoints = other.Hitpoints;
	Speed = other.Speed;
	PrimaryAttack = other.PrimaryAttack;
	SecondaryAttack = other.SecondaryAttack;
	Position = other.Position;
	Name = other.Name;
}

Unit::Unit(std::string name)
{
	IsSelected = false;
	MaxHitpoints = Hitpoints = 0;
	Speed = 0;
	PrimaryAttack = 0;
	SecondaryAttack = 0;
	Name = name;
}

Unit::~Unit()
{
}

Unit &Unit::operator=(const Unit &other)
{
	IsSelected = other.IsSelected;
	MaxHitpoints = other.MaxHitpoints;
	Hitpoints = other.Hitpoints;
	Speed = other.Speed;
	PrimaryAttack = other.PrimaryAttack;
	SecondaryAttack = other.SecondaryAttack;
	Position = other.Position;
	Name = other.Name;
	return *this;
}

//all of the following are incomplete!
short Unit::GetSpeedRating()
{
	return Speed;
}

short Unit::GetMeleeRating()
{
	return PrimaryAttack + SecondaryAttack;
}

short Unit::GetRangeRating()
{
	return SecondaryAttack;
}

void Unit::AttackUnit(Unit *other)
{
	other->Hitpoints -= PrimaryAttack;
}
