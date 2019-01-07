#include "SDLHost.h"

SDLHost::SDLHost()
{
	_running = false;
	_game = nullptr;
	_mapWidth = 14;
	_mapHeight = 8;
}

SDLHost::~SDLHost()
{
	delete _game;
}

bool SDLHost::Init(int argc, char **argv)
{
	_running = (SDL_Init(SDL_INIT_VIDEO) == 0);
	IMG_Init(IMG_INIT_JPG);
	_window = SDL_CreateWindow("MIGHT", 100, 100, 640, 400, 0);
	_renderSdl = new RenderSDL(_window);

	return _running;
}

void SDLHost::Exec(GameMaster *game)
{
	while(_running)
	{
		SDL_Event e;
		if(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
				_running = false;
		}

		//do the main game loop here

		_renderSdl->Render();
	}
}

void SDLHost::Quit()
{
	SDL_DestroyWindow(_window);
}
