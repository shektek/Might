#include "RenderSDL.h"
#include "AnimatedUnitFactory.h"
#include <cstring>

const char *imagesDir = "/home/luke/src/might/data/images/";
const char *battleBgImg = "field.jpg";
const char *borderHorImg = "simpleborder_hor.gif";
const char *borderVerImg = "simpleborder_ver.gif";
const char *swordsmanImg = "swordsman.gif";
const char *savageImg = "savage.gif";

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
	_unitRosterHeight = (windowHeight/100)*20;
	_worldInfoWidth = (windowWidth/100)*20;
	_viewportWidth = windowWidth - _borderWidth*2;
	_viewportHeight = windowHeight - (_borderHeight + _unitRosterHeight);
	_viewportOriginX = windowOriginX + _borderWidth;
	_viewportOriginY = windowOriginY + _borderHeight * 4;
	_unitRosterVisible = true;
	_worldInfoVisible = false;

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);


	char str[256] = {0};
	sprintf(str, "%s%s", imagesDir, battleBgImg);
	_backgroundSurface = _images.GetImage(str);
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

void RenderSDL::StartRender(double frameDelta)
{
	_frameDelta = frameDelta;
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(_renderer);
	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
}

void RenderSDL::RenderBorders()
{
	char buf[256] = {0};
	sprintf(buf, "%s%s", imagesDir, borderHorImg);
	SDL_Surface *sh = _images.GetImage(buf);
	memset(buf, 0, 256);
	sprintf(buf, "%s%s", imagesDir, borderVerImg);
	SDL_Surface *sv = _images.GetImage(buf);
	SDL_Texture *th = GetTexture(sh);
	SDL_Texture *tv = GetTexture(sv);

	SDL_Rect toprect { 0, 0, _windowWidth, _borderHeight };
	SDL_Rect bottomrect { 0, _windowHeight - _borderHeight, _windowWidth, _borderHeight };
	SDL_Rect leftrect { 0, _borderHeight, _borderWidth, _windowHeight - _borderHeight*2 };
	SDL_Rect rightrect { _windowWidth - _borderWidth, _borderHeight, _borderWidth, _windowHeight - _borderHeight*2 };
	SDL_RenderCopy(_renderer, th, NULL, &toprect);
	SDL_RenderCopy(_renderer, th, NULL, &bottomrect);
	SDL_RenderCopy(_renderer, tv, NULL, &leftrect);
	SDL_RenderCopy(_renderer, tv, NULL, &rightrect);
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

	int localWidth = width + _viewportOriginX;
	int localHeight = height + _viewportOriginY;
	int x = 0, y = 0;
	for(x = _viewportOriginX; x <= localWidth; x += _xGridSpacing)
	{
		SDL_RenderDrawLine(_renderer, x, _viewportOriginY, x, localHeight);
	}

	for(y = _viewportOriginY; y <= localHeight; y += _yGridSpacing)
	{
		SDL_RenderDrawLine(_renderer, _viewportOriginX, y, localWidth, y);
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

				SDL_Rect rect { _viewportOriginX + blCorner.x, _viewportOriginY + blCorner.y, _xGridSpacing, _yGridSpacing };

				SDL_RenderFillRect(_renderer, &rect);
			}
		}
	}
}

//TODO: This should cache AnimatedUnits in order to prevent casting every frame!
void RenderSDL::RenderLeftPlayer(Player *player)
{
	for(int i = 0; i < player->army->GetUnitCount(); i++)
	{
		Unit *unit = player->army->GetUnitAt(i);
		if(unit != nullptr)
		{
			if(unit->GetType() == U_ANIMATED)
			{
				AnimatedUnit *animated = dynamic_cast<AnimatedUnit*>(unit);
				RenderUnit(animated, SDL_FLIP_NONE);
			}
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
			if(unit->GetType() == U_ANIMATED)
			{
				AnimatedUnit *animated = dynamic_cast<AnimatedUnit*>(unit);
				RenderUnit(animated, SDL_FLIP_HORIZONTAL);
			}
		}
	}
}

void RenderSDL::RenderUnit(AnimatedUnit *unit, SDL_RendererFlip sdlFlip)
{
	AnimatedImage *curImg = unit->GetCurrentAnimation();
	SDL_Texture *t = nullptr;
	SDL_Surface *s = nullptr;
	SDL_Rect *framerect = nullptr;

	//TODO: Scale these to the tile size
	int scaledwidth = 96, scaledheight = 96;
	//adjust to view coordinates, remember that SDLRect draws from topleft so we need to subtract the height
	SDL_Rect posrect = { _viewportOriginX + unit->GetPosition().x, (_viewportOriginY + unit->GetPosition().y) - scaledheight/2, scaledwidth, scaledheight };

	curImg->GetCurrentFrame(s, framerect);
	t = GetTexture(s);

	SDL_RenderCopyEx(_renderer, t, framerect, &posrect, 0, NULL, sdlFlip);
}

void RenderSDL::RenderSelectionHighlight(BattleMap *map, Point2D position)
{
	Tile *location = map->GetContainingTile(position);
	if(location != nullptr)
	{
		Point2D bl = location->GlobalBottomLeft();

		SDL_SetRenderDrawColor(_renderer, 255, 255, 64, 100);
		SDL_Rect rect { _viewportOriginX + (int)((double)bl.x+_xGridSpacing*0.075), _viewportOriginY + (int)((double)bl.y+_yGridSpacing*0.075), (int)(_xGridSpacing*0.9), (int)(_yGridSpacing*0.9) };

		SDL_RenderFillRect(_renderer, &rect);
	}
}

void RenderSDL::RenderMouseHover(BattleMap *map, int mouseX, int mouseY)
{
	//if the mouse is on the map somewhere
	if(mouseX >= _viewportOriginX && mouseX < _viewportOriginX+_viewportWidth
		&& mouseY >= _viewportOriginY && mouseY < _viewportOriginY+_viewportHeight)
	{
		//find the tile that the mouse is in
		short normX = mouseX - _viewportOriginX;
		short normY = mouseY - _viewportOriginY;

		//for now...
		RenderSelectionHighlight(map, Point2D{normX, normY});
	}
}

void RenderSDL::FinishRender()
{
	SDL_RenderPresent(_renderer);
}

void RenderSDL::ScreenspaceToMapspace(int *x, int *y)
{
	*x -= _viewportOriginX;
	*y -= _viewportOriginY;
}

