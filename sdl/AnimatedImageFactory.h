#ifndef ANIMATEDIMAGEFACTORY_H
#define ANIMATEDIMAGEFACTORY_H

#include <nlohmann/json.hpp>
#include "ImageCache.h"
#include "AnimatedImage.h"

using json = nlohmann::json;

class AnimatedImageFactory
{
	public:
		static AnimatedImage CreateAnimatedImage(json jsonTemplate, ImageCache *imageCache);
};

#endif
