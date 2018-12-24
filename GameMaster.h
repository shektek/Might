#ifndef GAME_MASTER_H
#define GAME_MASTER_H

#include <vector>
#include "Player.h"
#include "BattleMap.h"
#include "Army.h"
#include "Unit.h"

class GameMaster
{
	private:
		Player *_left;
		Player *_right;
		BattleMap *_map;
		Army *_leftArmy;
		Army *_rightArmy;
		Unit *_previousSelected;
		Unit *_currentSelected;

	public:
        GameMaster();
		GameMaster(Player *left, Player *right);

        //add players
        bool AddPlayer(Player *newPlayer);

		//arrange units, apply player bonuses, etc.
        void PrepareRound(BattleMap *map, ArrangementStrategy leftArrangement, ArrangementStrategy rightArrangement);
		void PrepareRound(BattleMap *map, Army *left, Army *right, ArrangementStrategy leftArrangement, ArrangementStrategy rightArrangement);

		//set this unit as the current selection
		void SelectUnit(Unit *unit);

		//check if any lingering spells affect units
		void ApplySpellEffects();

		//determine who starts the next round
		std::vector<Player*> GetInitiativeOrder();

        //apply end of round rules
		void EndRound();
};

#endif
