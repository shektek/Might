#include "QtHost.h"

QtHost::QtHost()
{

}

QtHost::~QtHost()
{

}

bool QtHost::Init(int argc, char **argv)
{
    _qtApp = new QApplication (argc, argv);
    _mainWindow = new RenderQt();

    _mainWindow->show();
}

void QtHost::Exec()
{
    _qtApp->exec();
}

void QtHost::Quit()
{
    delete _mainWindow;
    delete _qtApp;
}
