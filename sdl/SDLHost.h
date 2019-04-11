#ifndef SDLHOST_H
#define SDLHOST_H

#include "../GameMaster.h"
#include "../AppHost.h"
#include "RenderSDL.h"
#include <SDL2/SDL.h>

class SDLHost : public AppHost
{
	private:
		bool _running;
		GameMaster *_game;
		RenderSDL *_renderSdl;
		SDL_Window *_window;
		int _mapWidth;
		int _mapHeight;

		bool HandleEvents(GameMaster *game, Unit *selectedUnit);
	public:
		SDLHost();
		virtual ~SDLHost();

		bool Init(int argc, char **argv);
		void Exec(GameMaster *game);
		void Quit();
};

#endif
