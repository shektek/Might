#include "ArmyFactory.h"
#include <cstring>

bool ArmyFactory::_listsInitialised = false;
std::vector<std::string> ArmyFactory::_prefix = std::vector<std::string>();
std::vector<std::string> ArmyFactory::_affix = std::vector<std::string>();
std::vector<std::string> ArmyFactory::_types = std::vector<std::string>();

void ArmyFactory::Init()
{
    if(!ArmyFactory::_listsInitialised)
    {
        _prefix.push_back("Gul");
        _prefix.push_back("Dru");
        _prefix.push_back("Mal");
        _prefix.push_back("Grum");
        _prefix.push_back("Kag");
        _prefix.push_back("Zim");

        _affix.push_back("zar");
        _affix.push_back("alub");
        _affix.push_back("ik-atar");
        _affix.push_back("ablig");
        _affix.push_back("shash");

        _types.push_back("peasant");
        _types.push_back("infantry");
        _types.push_back("swordsman");
        _types.push_back("scout");

        _listsInitialised = true;
    }
}

Army *ArmyFactory::CreateTestingArmy(int unitCount)
{
    Init();
    Army *ret = new Army();
    for(int i = 0; i < unitCount; i++)
    {
        char lname[256] = {0};
        sprintf(lname, "%s%s %s", _prefix[rand()%_prefix.size()].c_str(), _affix[rand()%_affix.size()].c_str(), _types[rand()%_types.size()].c_str());
        short hpt = 5 + rand()%10;
	short spd = 4 + rand()%5;
	short atk = 2 + rand()%10;

	Unit *l = new Unit(hpt, spd, atk, atk, lname, Point2D(0,0));

        ret->AddUnit(l);
    }

    return ret;
}
