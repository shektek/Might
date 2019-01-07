#include <thread>
#include <QMetaType>
#include "QtHost.h"
#include "../../ArmyFactory.h"

QtHost::QtHost()
{
    _running = false;
    _mapWidth = 14;
    _mapHeight = 8;
}

QtHost::~QtHost()
{

}

bool QtHost::Init(int argc, char **argv)
{
    //these need to be kept for QT
    _argc = argc;
    _argv = new char*[argc];
    for(int i = 0; i < argc; i++)
    {
        int len = strlen(argv[i]);
        _argv[i] = new char[len];
        strncpy(_argv[i], argv[i], len);
    }

    _qtApp = new QApplication(_argc, _argv);
    _mainWindow = new RenderQt();

    //qRegisterMetaType<BattleMap>();
    //qRegisterMetaType<NavigableGrid>();
    QObject::connect(this, SIGNAL(MapChanged(BattleMap)),
                         _mainWindow, SLOT(SetBattleMap(BattleMap)));
    QObject::connect(this, SIGNAL(SubmapChanged(NavigableGrid)),
                         _mainWindow, SLOT(SetSubmap(NavigableGrid)));

    _mainWindow->show();

    _running = true;

    return _running;
}

void QtHost::GameLoop()
{
    Army *leftarmy = nullptr;
    Army *rightarmy = nullptr;
    Player *leftplayer = nullptr;
    Player *rightplayer = nullptr;

    //if(_testArmies)
    {
        leftarmy = ArmyFactory::CreateTestingArmy(6);
        rightarmy = ArmyFactory::CreateTestingArmy(6);
    }

    //if(_testPlayers)
    {
        leftplayer = new Player("left player", leftarmy);
        rightplayer = new Player("right player", rightarmy);

        _game->AddPlayer(leftplayer);
        _game->AddPlayer(rightplayer);
    }

    BattleMap map(_mapWidth, _mapHeight, leftarmy, rightarmy);
    //_mainWindow->SetBattleMap(&map);
    emit MapChanged(map);
    _game->PrepareRound(&map, AS_LEFT_DEFAULT, AS_RIGHT_DEFAULT);

    //battle loop
    while(_running)
    {
        _game->ApplySpellEffects();

        std::vector<Player*> player = _game->GetInitiativeOrder();

        for(int curPlayer = 0; curPlayer < 2; curPlayer++)
        {
            std::vector<Unit*> sortedUnits = player[curPlayer]->army->GetSpeedSorted();

            for(unsigned int i = 0; i < sortedUnits.size(); i++)
            {
                _game->SelectUnit(sortedUnits[i]);
                NavigableGrid submap = map.CreateFloodFillSubmap(sortedUnits[i]->Position, sortedUnits[i]->Speed);

                //_mainWindow->SetHighlights(&submap);
                emit SubmapChanged(submap);
            }
        }
    }

    _game->EndRound();
}

//host -> set battlemap (emit map changed)
//host -> set submap (emit submap changed)
//window -> receive events

static void GameThreadFunc(QtHost *host)
{
    host->GameLoop();
}

void QtHost::Exec(GameMaster *game)
{
    _game = game;

    std::thread gameThread(GameThreadFunc, this);
    gameThread.detach();

    _qtApp->exec();
}

void QtHost::Quit()
{
    delete _mainWindow;
    delete _qtApp;

    for(int i = 0; i < _argc; i++)
    {
        delete[] _argv[i];
    }

    delete[] _argv;
}
