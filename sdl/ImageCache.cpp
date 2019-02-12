#include "ImageCache.h"

ImageCache::~ImageCache()
{
	Clear();
}

SDL_Surface *ImageCache::GetImage(std::string filename)
{
	std::map<std::string, SDL_Surface*>::iterator it = _cache.find(filename);
	if(it == _cache.end())
	{
		SDL_Surface *s = IMG_Load(filename.c_str());
		it = _cache.insert(it, std::make_pair(filename, s));
	}
	return it->second;
}

void ImageCache::Clear()
{
	for(std::map<std::string, SDL_Surface*>::iterator it = _cache.begin();
		it != _cache.end(); it++)
	{
		SDL_FreeSurface(it->second);
	}

	_cache.clear();
}
