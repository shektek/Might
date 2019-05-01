#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Army.h"

//TODO: Finish and refactor

class Player
{
	public:
		Army *army;
		std::string Name;

		Player(std::string name, Army *army);

		std::string	GetName() { return Name; }
};

#endif
