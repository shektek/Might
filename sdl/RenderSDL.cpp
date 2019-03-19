#include "RenderSDL.h"

RenderSDL::RenderSDL(SDL_Window *win, int windowWidth, int windowHeight)
{
	_xGridSpacing = 0;
	_yGridSpacing = 0;
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	_window = win;

	_windowWidth = windowWidth;
	_windowHeight = windowHeight;
	short windowOriginX = 0;
	short windowOriginY = 0;

	_borderWidth = (windowWidth/100)*3;
	_borderHeight = (windowHeight/100)*3;
	_unitRosterHeight = (windowHeight/100)*15;
	_worldInfoWidth = (windowWidth/100)*20;
	_viewportWidth = windowWidth - _borderWidth*2;
	_viewportHeight = windowHeight - (_borderHeight + _unitRosterHeight);
	_viewportOriginX = windowOriginX + _borderWidth;
	_viewportOriginY = windowOriginY + _borderHeight;
	_unitRosterVisible = true;
	_worldInfoVisible = false;

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

void RenderSDL::RenderBorders()
{
	SDL_Surface *sh = _images.GetImage("/home/luke/src/might/data/images/simpleborder_hor.gif");
	SDL_Texture *th = GetTexture(sh);

	SDL_Rect toprect { 0, 0, _windowWidth, _borderHeight };
	SDL_Rect bottomrect { 0, _windowHeight - _borderHeight, _windowWidth, _borderHeight };
	SDL_RenderCopy(_renderer, th, NULL, &toprect);
	SDL_RenderCopy(_renderer, th, NULL, &bottomrect);

}

void RenderSDL::RenderMap(BattleMap *map)
{
	short width = _viewportWidth;
	short height = _viewportHeight;

	SDL_RenderCopy(_renderer, _backgroundTexture, NULL, NULL);

	//draw grid over the top
	_xGridSpacing = width / map->GetWidth();
	_yGridSpacing = height / map->GetHeight();

	map->RescaleTiles(_xGridSpacing, _yGridSpacing);

	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 200);

	//TODO: rounding errors make these lengths inadequate
	int x;
	for(x = _viewportOriginX; x < width; x += _xGridSpacing)
	{
		SDL_RenderDrawLine(_renderer, x, _viewportOriginY, x, height);
	}
	SDL_RenderDrawLine(_renderer, x, _viewportOriginY, x, height);

	int y;
	for(y = _viewportOriginY; y < height; y += _yGridSpacing)
	{
		SDL_RenderDrawLine(_renderer, _viewportOriginX, y, width, y);
	}
	SDL_RenderDrawLine(_renderer, _viewportOriginX, y, width, y);
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

//TODO: this really ought to call RenderUnit!
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

//TODO: take the bits from the Render Player functions above that render a unit
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
