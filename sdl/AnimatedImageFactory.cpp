#include "AnimatedImageFactory.h"
#include "../Tools.h"

using json = nlohmann::json;

AnimatedImage AnimatedImageFactory::CreateAnimatedImage(json jsonTemplate, ImageCache *imageCache)
{
	AnimatedImage result;

	for (auto &element : jsonTemplate)
	{
		std::string imageFile = Tools::GetInstance().ParseResourceString(element["imagefile"]);
		result.AddSurface(imageCache->GetImage(imageFile));
		for (auto &frame : element["frames"])
		{
			int x = frame["x"];
			int y = frame["y"];
			int w = frame["w"];
			int h = frame["h"];
			result.AddFrame(SDL_Rect{x, y, w, h});
		}
	}

	return result;
}
