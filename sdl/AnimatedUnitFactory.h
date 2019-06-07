#ifndef ANIMATEDUNITFACTORY_H
#define ANIMATEDUNITFACTORY_H

#include <string>
#include "AnimatedUnit.h"
#include <nlohmann/json.hpp>
#include "ImageCache.h"

using json = nlohmann::json;

class AnimatedUnitFactory
{
	public:
		//The unit spec file is the JSON unit template to be parsed
		static AnimatedUnit *CreateAnimatedUnit(std::string templateFilename, ImageCache *imageCache);
		static AnimatedUnit *CreateAnimatedUnit(json jsonTemplate, ImageCache *imageCache);
		static AnimatedUnit *CreateAnimatedUnit(Unit *other, AnimatedImage idleSet, AnimatedImage moveSet, AnimatedImage attackSet, AnimatedImage dieSet);
};

#endif
