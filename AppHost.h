#ifndef APPHOST_H
#define APPHOST_H

class AppHost
{
    public:
        virtual bool Init() = 0;
        virtual void Exec() = 0;
        virtual void Quit() = 0;
};

#endif
