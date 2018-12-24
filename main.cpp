#include <QApplication>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include "ConsoleHost.h"
#include "renderqt.h"

int main(int argc, char **argv)
{
    AppHost *app = new ConsoleHost();

    if(app->Init())
        app->Exec();

    app->Quit;

    delete app;

    QApplication qapp(argc, argv);
    RenderQt mainWindow;


    mainWindow.show();

    qapp.exec();


    //just stupid test data
    std::vector<std::string> sprefix =
    {
        "Gul",
        "Dru",
        "Mal",
        "Grum",
        "Kag",
        "Zim"
    };

    std::vector<std::string> saffix =
    {
        "zar",
        "alub",
        "ik-atar",
        "ablig",
        "shash"
    };

    std::vector<std::string> stypes =
    {
        "peasant",
        "infantry",
        "swordsman",
        "scout"
    };

    srand((unsigned)time(0));

    Army *left = new Army();
	Army *right = new Army();

	for(int i = 0; i < 6; i++)
	{
		char lname[256] = {0};
		char rname[256] = {0};
        sprintf(lname, "%s%s %s", sprefix[rand()%sprefix.size()].c_str(), saffix[rand()%saffix.size()].c_str(), stypes[rand()%stypes.size()].c_str());
        sprintf(rname, "%s%s %s", sprefix[rand()%sprefix.size()].c_str(), saffix[rand()%saffix.size()].c_str(), stypes[rand()%stypes.size()].c_str());
		Unit *l = new Unit(lname);
		Unit *r = new Unit(rname);

		l->MaxHitpoints = l->Hitpoints = r->MaxHitpoints = r->Hitpoints = 10;
		l->Speed = 4 + rand()%5;
		r->Speed = 4 + rand()%5;
		l->PrimaryAttack = r->PrimaryAttack = 4;

		left->AddUnit(l);
		right->AddUnit(r);
	}

	Player *playerOne = new Player("player 1", left);
	Player *playerTwo = new Player("player 2", right);

	GameMaster game(playerOne, playerTwo);

    const int MapWidth = 14;
    const int MapHeight = 8;

    BattleMap map(MapWidth, MapHeight, left, right);
	game.PrepareRound(&map, left, right, AS_LEFT_DEFAULT, AS_RIGHT_DEFAULT);



	game.EndRound();

	delete left;
	delete right;


	return 0;
}
