#include "RenderSDL.h"

RenderSDL::RenderSDL(SDL_Window *win, int windowWidth, int windowHeight)
{
	_xGridSpacing = 0;
	_yGridSpacing = 0;
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	_window = win;
	_windowWidth = windowWidth;
	_windowHeight = windowHeight;
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	_backgroundSurface = _images.GetImage("/home/luke/src/might/data/images/field.jpg");
	_backgroundTexture = SDL_CreateTextureFromSurface(_renderer, _backgroundSurface);
}

RenderSDL::~RenderSDL()
{
	_images.Clear();
	ClearTextures();
	SDL_DestroyTexture(_backgroundTexture);
	SDL_DestroyRenderer(_renderer);

	IMG_Quit();
}

SDL_Texture *RenderSDL::GetTexture(SDL_Surface *surface)
{
	std::map<SDL_Surface *, SDL_Texture *>::iterator it = _loadedTextures.find(surface);
	if(it == _loadedTextures.end())
	{
		SDL_Texture *t = SDL_CreateTextureFromSurface(_renderer, surface);
		it = _loadedTextures.insert(it, std::make_pair(surface, t));
	}
	return it->second;
}

void RenderSDL::ClearTextures()
{
	for(std::map<SDL_Surface *, SDL_Texture *>::iterator it = _loadedTextures.begin();
		it != _loadedTextures.end(); it++)
	{
		SDL_DestroyTexture(it->second);
	}

	_loadedTextures.clear();
}

void RenderSDL::StartRender()
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(_renderer);
	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
}

void RenderSDL::RenderMap(BattleMap *map)
{
	SDL_RenderCopy(_renderer, _backgroundTexture, NULL, NULL);

	//draw grid over the top
	_xGridSpacing = _windowWidth / map->GetWidth();
	_yGridSpacing = _windowHeight / map->GetHeight();

	map->RescaleTiles(_xGridSpacing, _yGridSpacing);

	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 200);

	for(int x = 0; x < _windowWidth; x += _xGridSpacing)
	{
		SDL_RenderDrawLine(_renderer, x, 0, x, _windowHeight);
	}

	for(int y = 0; y < _windowHeight; y += _yGridSpacing)
	{
		SDL_RenderDrawLine(_renderer, 0, y, _windowWidth, y);
	}
}

void RenderSDL::RenderSubmap(NavigableGrid *submap)
{
	for(int xi = 0; xi < submap->GetWidth(); xi++)
	{
		for(int yi = 0; yi < submap->GetHeight(); yi++)
		{
			TileFloodNode *node = submap->GetTile(xi, yi);

			if(node != nullptr)
			{
				Point2D blCorner = node->tile->GlobalBottomLeft();
				Point2D centre = node->tile->GlobalCentre();

				if(node->prev != nullptr)
				{
					//draw a line from here to prev
					SDL_SetRenderDrawColor(_renderer, 255, 255, 64, 255);
					Point2D prevPos = node->prev->tile->GlobalCentre();
					SDL_RenderDrawLine(_renderer, prevPos.x, prevPos.y, centre.x, centre.y);

					SDL_SetRenderDrawColor(_renderer, 0, 64, 200, 100);
				}
				else
					SDL_SetRenderDrawColor(_renderer, 100, 0, 0, 50);

				SDL_Rect rect { blCorner.x, blCorner.y, _xGridSpacing, _yGridSpacing };

				SDL_RenderFillRect(_renderer, &rect);
			}
		}
	}
}

void RenderSDL::RenderLeftPlayer(Player *player)
{
	for(int i = 0; i < player->army->GetUnitCount(); i++)
	{
		Unit *unit = player->army->GetUnitAt(i);
		if(unit != nullptr)
		{
			SDL_Surface *s = _images.GetImage("/home/luke/src/might/data/images/swordsman.gif");
			SDL_Texture *t = GetTexture(s);

			SDL_Rect rect { unit->Position.x, unit->Position.y, 128, 128 };
			//SDL_Rect rect { unit->Position.x, unit->Position.y, _xGridSpacing, _yGridSpacing };
			SDL_RenderCopy(_renderer, t, NULL, &rect);
		}
	}
}

void RenderSDL::RenderRightPlayer(Player *player)
{
	for(int i = 0; i < player->army->GetUnitCount(); i++)
	{
		Unit *unit = player->army->GetUnitAt(i);
		if(unit != nullptr)
		{
			SDL_Surface *s = _images.GetImage("/home/luke/src/might/data/images/swordsman.gif");
			SDL_Texture *t = GetTexture(s);

			SDL_Rect rect { unit->Position.x, unit->Position.y, _xGridSpacing, _yGridSpacing };
			SDL_RenderCopyEx(_renderer, t, NULL, &rect, 0, NULL, SDL_FLIP_HORIZONTAL);
		}
	}
}

void RenderSDL::RenderUnit(Unit *unit)
{

}

void RenderSDL::RenderSelectionHighlight(BattleMap *map, Point2D position)
{
	Tile *location = map->GetContainingTile(position);
	if(location != nullptr)
	{
		Point2D bl = location->GlobalBottomLeft();

		SDL_SetRenderDrawColor(_renderer, 255, 255, 64, 100);
		SDL_Rect rect { (double)bl.x+_xGridSpacing*0.075, (double)bl.y+_yGridSpacing*0.075, _xGridSpacing*0.9, _yGridSpacing*0.9 };

		SDL_RenderFillRect(_renderer, &rect);
	}
}

void RenderSDL::FinishRender()
{
	SDL_RenderPresent(_renderer);
}
