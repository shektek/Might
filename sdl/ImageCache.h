#ifndef IMAGECACHE_H
#define IMAGECACHE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>

class ImageCache
{
	private:
		std::map<std::string, SDL_Surface*> _cache;

	public:
		~ImageCache();

		SDL_Surface *GetImage(std::string filename);
		void Clear();

};

#endif
