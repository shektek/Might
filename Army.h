#ifndef ARMY_H
#define ARMY_H

#include <vector>
#include <string>
#include "Unit.h"

class Army
{
	/* An army stores the stacks of units available to a player.
	 * This class is not complete!
	 */
	private:
		std::vector<Unit*> _units;

	public:
		Army();
		Army(const Army &other);
		~Army();

		Army &operator=(const Army &other);

		std::string Name;

		int GetUnitCount() { return _units.size(); }
		Unit *GetUnitAt(int index);
		void RemoveUnit(Unit *unit);
		void AddUnit(Unit *unit);
		bool FindUnit(Unit *unit);
		void DeselectAll();
		void SelectUnit(Unit *unit);

		std::vector<Unit*> GetSpeedSorted();
		std::vector<Unit*> GetMeleeSorted();
		std::vector<Unit*> GetRangeSorted();
};

#endif
