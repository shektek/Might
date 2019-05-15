#ifndef FACTION_H
#define FACTION_H

#include <string>
#include <vector>
#include "Unit.h"

enum FactionType
{
	F_NONE,
	F_DATHLORN,
	F_KUSHKULN,
	F_ZYRIADIBULN,
	F_MEDRANIS,
	F_UNDEAD,
	F_ELEMENTAL,
	F_SUN,
	F_MAX
};

class Faction
{
	private:
		FactionType		_factionType;
		std::string		_name;
		std::vector<Unit*>	_unitRoster;
		//std::vector<Hero*>	_heroRoster;

	public:
		Faction();
		Faction(const Faction &other);
		Faction(FactionType factionType, std::string name, std::vector<Unit*> unitRoster);

		Faction &operator=(const Faction &other);

		~Faction();

		FactionType		GetFactionType() { return _factionType; }
		std::string		GetName() { return _name; }
		std::vector<Unit*>	GetUnitRoster() { return _unitRoster; }
};

#endif
