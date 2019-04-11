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
		if(e.type == SDL_MOUSEBUTTONDOWN)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			map->MoveUnitToPosition(selectedUnit, x, y);
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

	while(_running)
	{
		auto *selectedUnit = _game->GetSelectedUnit();
		_running = HandleEvents(_game, selectedUnit);

		int mousex = 0, mousey = 0;
		SDL_GetMouseState(&mousex, &mousey);

		NavigableGrid submap = map.CreateFloodFillSubmap(selectedUnit->Position, selectedUnit->Speed);

		_renderSdl->StartRender();
		_renderSdl->RenderMap(&map);
		_renderSdl->RenderSubmap(&submap);
		_renderSdl->RenderSelectionHighlight(&map, selectedUnit->Position);
		_renderSdl->RenderLeftPlayer(_game->GetLeftPlayer());
		_renderSdl->RenderRightPlayer(_game->GetRightPlayer());
		_renderSdl->RenderBorders();
		_renderSdl->RenderMouseHover(&map, mousex, mousey);
		_renderSdl->FinishRender();
	}
}

void SDLHost::Quit()
{
	SDL_DestroyWindow(_window);
}
