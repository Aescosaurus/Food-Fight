#pragma once

#include <vector>
#include "Table.h"
#include "Food.h"
#include "Door.h"

class LevelReader
{
public:
	void ReadLevelIntoArrays( const int nLevel,std::vector<Table>& tables,
		std::vector<HotDog>& hotDogs,
		std::vector<Meatball>& meatballs,
		std::vector<Door>& doors );
private:
};