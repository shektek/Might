#ifndef ARMYFACTORY_H
#define ARMYFACTORY_H

#include "Army.h"
#include <vector>

class ArmyFactory
{
    public:
        static bool _listsInitialised;

        static std::vector<std::string> _prefix;

        static std::vector<std::string> _affix;

        static std::vector<std::string> _types;

        static void Init();

    public:
        static Army *CreateTestingArmy(int unitCount);
};

#endif // ARMYFACTORY_H
