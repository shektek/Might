#ifndef RENDERSDL_H
#define RENDERSDL_H

#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Player.h"
#include "../BattleMap.h"
#include "../NavigableGrid.h"
#include "ImageCache.h"
#include "AnimatedUnit.h"

class RenderSDL
{
	private:
		short _viewportWidth;
		short _viewportHeight;
		short _viewportOriginX;
		short _viewportOriginY;

		short _borderWidth;
		short _borderHeight;
		short _unitRosterHeight;
		short _worldInfoWidth;
		bool _unitRosterVisible;
		bool _worldInfoVisible;

		int _windowWidth;
		int _windowHeight;
		int _xGridSpacing;
		int _yGridSpacing;

		double _frameDelta;
		SDL_Renderer *_renderer;
		SDL_Window *_window;
		SDL_Surface *_backgroundSurface;
		SDL_Texture *_backgroundTexture;
		ImageCache _images;
		std::map<SDL_Surface*, SDL_Texture *> _loadedTextures;

		void ClearTextures();

	public:
		RenderSDL(SDL_Window *win, int windowWidth, int windowHeight);
		virtual ~RenderSDL();

		void StartRender(double frameDelta);
		void RenderBorders();
		void RenderUnitRoster();
		void RenderWorldInfo();
		void RenderMap(BattleMap *map);
		void RenderSubmap(NavigableGrid *submap);
		void RenderLeftPlayer(Player *player);
		void RenderRightPlayer(Player *player);
		void RenderUnit(AnimatedUnit *unit, SDL_RendererFlip sdlFlip);
		void RenderSelectionHighlight(BattleMap *map, Point2D position);
		void RenderMouseHover(BattleMap *map, int mouseX, int mouseY);
		void FinishRender();

		void ScreenspaceToMapspace(int *x, int *y);
		SDL_Texture *GetTexture(SDL_Surface *surface);

		SDL_Renderer *GetRenderer() { return _renderer; } //temp
};

#endif
