#include "SDLHost.h"
#include "../ArmyFactory.h"

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
	_running = (SDL_Init(SDL_INIT_EVERYTHING) == 0);
	int width = 800;
	int height = 600;
	_window = SDL_CreateWindow("MIGHT", 100, 100, width, height, 0);
	_renderSdl = new RenderSDL(_window, width, height);

	return _running;
}

bool SDLHost::HandleEvents(GameMaster *game, Unit *selectedUnit)
{
	bool result = true;
	SDL_Event e;

	BattleMap *map = game->GetBattleMap();

	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT)
			result = false;
		if(e.type == SDL_KEYUP)
		{
			if(e.key.keysym.sym == SDLK_SPACE)
			{
				//maybe check which key first
				game->StepRound();
			}
		}
		if(e.type == SDL_MOUSEBUTTONUP)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			_renderSdl->ScreenspaceToMapspace(&x, &y);
			map->MoveUnitToPosition(selectedUnit, Point2D(x, y));
		}
	}

	return result;
}

void SDLHost::Exec(GameMaster *game)
{
	_game = game;

	_game->AddPlayer(new Player("leftplayer", ArmyFactory::CreateTestingArmy(6)));
	_game->AddPlayer(new Player("rightplayer", ArmyFactory::CreateTestingArmy(6)));

	BattleMap map(_mapWidth, _mapHeight, _game->GetLeftPlayer()->army, _game->GetRightPlayer()->army);
	_game->PrepareRound(&map, AS_LEFT_DEFAULT, AS_RIGHT_DEFAULT);
	NavigableGrid submap;
	Unit *lastSelected = nullptr;
	Unit *selectedUnit = nullptr;

	double frameStart = 0, frameEnd = SDL_GetTicks(), frameDelta = 0;

	while(_running)
	{
		frameStart = SDL_GetTicks();
		frameDelta = frameEnd - frameStart;
		lastSelected = selectedUnit;
		selectedUnit = _game->GetSelectedUnit();
		_running = HandleEvents(_game, selectedUnit);

		int mousex = 0, mousey = 0;
		SDL_GetMouseState(&mousex, &mousey);

		if(lastSelected != selectedUnit)
			submap = map.CreateFloodFillSubmap(selectedUnit->GetPosition(), selectedUnit->GetRemainingMovement());

		_renderSdl->StartRender(frameDelta);
		_renderSdl->RenderMap(&map);
		_renderSdl->RenderSubmap(&submap);
		_renderSdl->RenderSelectionHighlight(&map, selectedUnit->GetPosition());
		_renderSdl->RenderLeftPlayer(_game->GetLeftPlayer());
		_renderSdl->RenderRightPlayer(_game->GetRightPlayer());
		_renderSdl->RenderBorders();
		_renderSdl->RenderMouseHover(&map, mousex, mousey);
		_renderSdl->FinishRender();

		frameEnd = SDL_GetTicks();
	}
}

void SDLHost::Quit()
{
	SDL_DestroyWindow(_window);
}
