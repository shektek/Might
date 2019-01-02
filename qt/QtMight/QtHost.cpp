#include "QtHost.h"

QtHost::QtHost()
{
    _running = false;
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

    _mainWindow->show();

    _running = true;

    return _running;
}

void QtHost::Exec()
{
    _qtApp->exec();

    while(_running);
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
