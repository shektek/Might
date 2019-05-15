#include "Faction.h"

Faction::Faction()
{
	_factionType = F_NONE;
	_name = "None";
}

Faction::Faction(const Faction &other)
{
	_factionType = other._factionType;
	_name = other._name;
	_unitRoster = other._unitRoster;
	//_heroRoster = other._heroRoster;
}

Faction::Faction(FactionType factionType, std::string name, std::vector<Unit*> unitRoster)
{
	_factionType = factionType;
	_name = name;
	_unitRoster = unitRoster;
}

Faction &Faction::operator=(const Faction &other)
{
	_factionType = other._factionType;
	_name = other._name;
	_unitRoster = other._unitRoster;

	return *this;
}

Faction::~Faction()
{
	_factionType = F_NONE;
	_name.clear();
	for(unsigned int i = 0; i < _unitRoster.size(); i++)
	{
		delete _unitRoster[i];
		_unitRoster[i] = nullptr;
	}
	_unitRoster.clear();
}
