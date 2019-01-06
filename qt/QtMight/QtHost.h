#ifndef QTHOST_H
#define QTHOST_H

#include "../../AppHost.h"
#include <QApplication>
#include "RenderQt.h"

class QtHost : public QObject, public AppHost
{
        Q_OBJECT

    private:
        int _argc;
        char **_argv;

        QApplication *_qtApp;
        RenderQt *_mainWindow;

        GameMaster *_game;
        bool _running;
        short _mapWidth;
        short _mapHeight;

    public:
        QtHost();
        virtual ~QtHost();

        bool Init(int argc, char **argv);
        void Exec(GameMaster *game);
        void Quit();

        void GameLoop();

    signals:
        void MapChanged(BattleMap newMap);
        void SubmapChanged(NavigableGrid newSubmap);
};

#endif // QTHOST_H
