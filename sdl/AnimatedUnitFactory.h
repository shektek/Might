#ifndef ANIMATEDUNITFACTORY_H
#define ANIMATEDUNITFACTORY_H

#include <string>
#include "AnimatedUnit.h"

class AnimatedUnitFactory
{
	public:
		//The unit spec file is the JSON unit template to be parsed
		static AnimatedUnit *CreateAnimatedUnit(std::string unitSpecFile);
		static AnimatedUnit *CreateAnimatedUnit(Unit *other, std::string unitSpecFile);
};

#endif
