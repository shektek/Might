#include "SDLHost.h"
#include "../ArmyFactory.h"
#include "AnimatedImage.h"
#include "AnimatedUnitFactory.h"
#include "../Tools.h"

SDLHost::SDLHost()
{
	_renderSdl = nullptr;
	_window = nullptr;
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
	InitDataFolder();
	_running = (SDL_Init(SDL_INIT_EVERYTHING) == 0);
	int width = 800;
	int height = 600;
	_window = SDL_CreateWindow("MIGHT", 100, 100, width, height, 0);
	_renderSdl = new RenderSDL(_window, width, height);

	return _running;
}

void SDLHost::InitDataFolder()
{
	//first try to open the dirs.txt file
	//if it doesn't exist, create a default one
	//otherwise just open it and get the absolute folder directory

	FILE* f = fopen("dirs.txt", "r");
	if (f)
	{
		int linenum = 0;
		char line[1024] = { 0 };
		while (fgets(line, 1024, f))
		{
			switch (linenum)
			{
			case 0:
				Tools::GetInstance().DataDirectory = line;
				break;
			}


			linenum++;
		}

		fclose(f);
	}
}

bool SDLHost::HandleEvents(GameMaster *game, Unit *selectedUnit)
{
	bool result = true;
	SDL_Event e;

	BattleMap *map = nullptr;
	if(game)
		map = game->GetBattleMap();

	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT)
			result = false;
		if(e.type == SDL_KEYUP)
		{
			if(e.key.keysym.sym == SDLK_SPACE)
			{
				if(game)
					game->StepRound();
			}
		}
		if(e.type == SDL_MOUSEBUTTONUP)
		{
			if(map)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				_renderSdl->ScreenspaceToMapspace(&x, &y);
				map->MoveUnitToPosition(selectedUnit, Point2D(x, y));
			}
		}
	}

	return result;
}

void SDLHost::Test()
{
	AnimatedImage animTest;
	ImageCache tempCache;
	SDL_Surface *swordsman = tempCache.GetImage(Tools::GetInstance().DataDirectory + "images/swordsman.gif");
	SDL_Surface *savage = tempCache.GetImage(Tools::GetInstance().DataDirectory + "images/savage.gif");
	SDL_Surface *frmtst = tempCache.GetImage(Tools::GetInstance().DataDirectory + "images/frametest.gif");
	animTest.AddSurface(swordsman);
	animTest.AddSurface(savage);
	animTest.AddSurface(frmtst);
	animTest.AddFrame(SDL_Rect{0, 0, 127, 127});
	animTest.AddFrame(SDL_Rect{129, 0, 127, 127});
	animTest.AddFrame(SDL_Rect{258, 0, 127, 127});

	SDL_Surface *bgs = tempCache.GetImage(Tools::GetInstance().DataDirectory + "images/field.jpg");
	auto bgt = SDL_CreateTextureFromSurface(_renderSdl->GetRenderer(), bgs);

	SDL_Surface *seet = nullptr;
	SDL_Rect *reet = nullptr;
	animTest.GetCurrentFrame(seet, reet);

	unsigned int frameStart = 0, frameEnd = SDL_GetTicks(), frameDelta = 0, frameTotal = 0;
	while(_running)
	{
		frameStart = SDL_GetTicks();
		frameDelta = frameEnd - frameStart;

		_running = HandleEvents(nullptr, nullptr);

		_renderSdl->StartRender((double)frameDelta);
		SDL_Surface *s = nullptr;
		SDL_Rect *r = nullptr;

		animTest.GetCurrentFrame(s, r);

		SDL_Texture *t = _renderSdl->GetTexture(s);
		SDL_Rect posr {0, 0, 128, 128};

		SDL_RenderCopy(_renderSdl->GetRenderer(), bgt, NULL, NULL);

		SDL_RenderCopyEx(_renderSdl->GetRenderer(), t, r, &posr, 0, NULL, SDL_FLIP_NONE);

		_renderSdl->FinishRender();

		frameEnd = SDL_GetTicks();
		frameTotal += frameDelta + 1;

		if(frameTotal % 500 == 0)
		{
			frameDelta += 1;
			if(r)
			{
				printf("x %d y %d w %d h %d\n", r->x, r->y, r->w, r->h);
			}

			animTest.Rewind();
		}
	}
}

void SDLHost::Exec(GameMaster *game)
{
//	Test();
	ImageCache *imageCache = new ImageCache();

	_game = game;

	Army *leftArmy = new Army();
	Army *rightArmy = new Army();

	std::string swordsmanPath = Tools::GetInstance().DataDirectory + "units/swordsman.json";
	std::string savagePath = Tools::GetInstance().DataDirectory + "units/savage.json";

	leftArmy->AddUnit(AnimatedUnitFactory::CreateAnimatedUnit(swordsmanPath, imageCache));
	leftArmy->AddUnit(AnimatedUnitFactory::CreateAnimatedUnit(swordsmanPath, imageCache));

	rightArmy->AddUnit(AnimatedUnitFactory::CreateAnimatedUnit(savagePath, imageCache));
	rightArmy->AddUnit(AnimatedUnitFactory::CreateAnimatedUnit(savagePath, imageCache));

	_game->AddPlayer(new Player("leftplayer", leftArmy));
	_game->AddPlayer(new Player("rightplayer", rightArmy));

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
