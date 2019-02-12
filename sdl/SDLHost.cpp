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
	int width = 640;
	int height = 400;
	_window = SDL_CreateWindow("MIGHT", 100, 100, width, height, 0);
	_renderSdl = new RenderSDL(_window, width, height);

	return _running;
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
		SDL_Event e;

		//this has to happen before player input
		_game->ApplySpellEffects();

		std::vector<Player*> players = _game->GetInitiativeOrder();

		//if player == me, allow certain actions

		//for now just let both players do stuff
		for(int curPlayer = 0; curPlayer < 2; curPlayer++)
		{
			std::vector<Unit*> sortedUnits = players[curPlayer]->army->GetSpeedSorted();

			for(unsigned int i = 0; i < sortedUnits.size(); i++)
			{
				game->SelectUnit(sortedUnits[i]);
				NavigableGrid submap = map.CreateFloodFillSubmap(sortedUnits[i]->Position, sortedUnits[i]->Speed);

				_renderSdl->StartRender();
				_renderSdl->RenderMap(&map);
				_renderSdl->RenderSubmap(&submap);
				_renderSdl->RenderSelectionHighlight(&map, sortedUnits[i]->Position);
				_renderSdl->RenderLeftPlayer(_game->GetLeftPlayer());
				_renderSdl->RenderRightPlayer(_game->GetRightPlayer());
				_renderSdl->FinishRender();

				bool spacePressed = false;
				do
				{
					if(SDL_PollEvent(&e))
					{
						if(e.type == SDL_QUIT)
							_running = false;
						if(e.type == SDL_KEYDOWN)
						{//maybe check which key first
							spacePressed = true;
						}
						if(e.type == SDL_MOUSEBUTTONDOWN)
						{
							int x, y;
							SDL_GetMouseState(&x, &y);
							map.MoveUnitToPosition(sortedUnits[i], x, y);
						}
					}

					if(_running && !spacePressed)
						SDL_Delay(100);
				} while (!spacePressed && _running);
			}
		}
	}
}

void SDLHost::Quit()
{
	SDL_DestroyWindow(_window);
}
