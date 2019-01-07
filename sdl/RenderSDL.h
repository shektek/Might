#ifndef RENDERSDL_H
#define RENDERSDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class RenderSDL
{
	private:
		SDL_Renderer *_renderer;
		SDL_Window *_window;
		SDL_Surface *_backgroundSurface;
		SDL_Texture *_backgroundTexture;

	public:
		RenderSDL(SDL_Window *win);
		virtual ~RenderSDL();

		void Render();
};

#endif
