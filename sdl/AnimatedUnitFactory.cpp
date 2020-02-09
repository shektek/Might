#include "AnimatedUnitFactory.h"
#include "AnimatedImageFactory.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "../Tools.h"

using json = nlohmann::json;

AnimatedUnit *AnimatedUnitFactory::CreateAnimatedUnit(std::string unitSpecFile, ImageCache *imageCache)
{

	std::ifstream jsonFile(unitSpecFile);
	json j;
	jsonFile >> j;

	return CreateAnimatedUnit(j, imageCache);
}

AnimatedUnit *AnimatedUnitFactory::CreateAnimatedUnit(json jsonTemplate, ImageCache *imageCache)
{
	int maxHp = jsonTemplate["maxhitpoints"];
	int spd = jsonTemplate["speed"];
	int prmAtk = jsonTemplate["primaryattack"];
	int scdAtk = jsonTemplate["secondaryattack"];
	std::string name = jsonTemplate["name"];
	Point2D pos;
	std::string portrait = Tools::GetInstance().ParseResourceString(jsonTemplate["portraitfile"]);

	AnimatedImage idleSet = AnimatedImageFactory::CreateAnimatedImage(jsonTemplate["idleset"], imageCache);
	AnimatedImage moveSet = AnimatedImageFactory::CreateAnimatedImage(jsonTemplate["moveset"], imageCache);
	AnimatedImage attackSet = AnimatedImageFactory::CreateAnimatedImage(jsonTemplate["attackset"], imageCache);
	AnimatedImage dieSet = AnimatedImageFactory::CreateAnimatedImage(jsonTemplate["dieset"], imageCache);

	return new AnimatedUnit(maxHp, spd, prmAtk, scdAtk, name, pos, portrait, idleSet, moveSet, attackSet, dieSet);
}

AnimatedUnit *AnimatedUnitFactory::CreateAnimatedUnit(Unit *other, AnimatedImage idleSet, AnimatedImage moveSet, AnimatedImage attackSet, AnimatedImage dieSet)
{
	AnimatedUnit *result = new AnimatedUnit(*other);
	result->SetIdleAnimationSet(idleSet);
	result->SetMoveAnimationSet(moveSet);
	result->SetAttackAnimationSet(attackSet);
	result->SetDieAnimationSet(dieSet);

	return result;
}
