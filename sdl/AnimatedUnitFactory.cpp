#include "AnimatedUnitFactory.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <stringstream>

using json = nlohmann::json;

AnimatedUnit *AnimatedUnitFactory::CreateAnimatedUnit(std::string unitSpecFile)
{

	std::ifstream jsonFile(unitSpecFile);
	json parsed;
	jsonFile >> parsed;

	
}

/*
example JSON unit file

	{
		"name": "TestUnit",
		"maxhitpoints": 10,
		"speed": 5,
		"primaryattack": 3,
		"secondaryattack": 4,
		"idleset": [
			{
				"imagefile": "/home/luke/src/might/data/images/frametest.gif",
				"frames": [
					{ "x":   0, "y": 0, "w": 127, "h": 127 },
					{ "x": 128, "y": 0, "w": 127, "h": 127 },
					{ "x": 256, "y": 0, "w": 127, "h": 127 }
				]
			}
		],
		"moveset": [

		],
		"attackset": [

		],
		"dieset": [

		]
	}

*/
