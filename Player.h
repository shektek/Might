#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Army.h"

class Player
{
	public:
		Army *army;
		std::string Name;

		Player(std::string name, Army *army);
};

#endif
