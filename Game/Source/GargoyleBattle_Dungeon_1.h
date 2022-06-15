#ifndef __GARGOYLE_BATTLE_DUNGEON_1_H__
#define __GARGOYLE_BATTLE_DUNGEON_1_H__

#include "GargoyleBattle.h"

class Scene;

class GargoyleBattle_Dungeon_1 : public GargoyleBattle {
public:
	GargoyleBattle_Dungeon_1();
	~GargoyleBattle_Dungeon_1();

	void SetBattlefield() override;
};

#endif  // __LOG_H__