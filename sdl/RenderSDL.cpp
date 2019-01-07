#include "RenderSDL.h"

RenderSDL::RenderSDL(SDL_Window *win)
{
	_window = win;
	_renderer = SDL_CreateRenderer(_window, -1, 0);
	_backgroundSurface = IMG_Load("../data/images/field.jpg");
	_backgroundTexture = SDL_CreateTextureFromSurface(_renderer, _backgroundSurface);

	//_backgroundTexture = IMG_LoadTexture(_renderer, "../data/images/field.jpg");
}

RenderSDL::~RenderSDL()
{
	SDL_DestroyTexture(_backgroundTexture);
	SDL_DestroyRenderer(_renderer);

	IMG_Quit();
}

void RenderSDL::Render()
{
	//SDL_RenderClear(_renderer);
	SDL_RenderCopy(_renderer, _backgroundTexture, NULL, NULL);
	SDL_RenderPresent(_renderer);
}
