#ifndef QTHOST_H
#define QTHOST_H

#include "../../AppHost.h"
#include <QApplication>
#include "RenderQt.h"

class QtHost : public AppHost
{
    private:
        int _argc;
        char **_argv;

        QApplication *_qtApp;
        RenderQt *_mainWindow;

        bool _running;

    public:
        QtHost();
        ~QtHost();

        bool Init(int argc, char **argv);
        void Exec();
        void Quit();
};

#endif // QTHOST_H
