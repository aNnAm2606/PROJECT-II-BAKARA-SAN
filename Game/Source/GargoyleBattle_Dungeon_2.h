#ifndef __GARGOYLE_BATTLE_DUNGEON_2_H__
#define __GARGOYLE_BATTLE_DUNGEON_2_H__

#include "GargoyleBattle.h"

class Scene;

class GargoyleBattle_Dungeon_2 : public GargoyleBattle {
public:
	GargoyleBattle_Dungeon_2();
	~GargoyleBattle_Dungeon_2();

	void SetBattlefield() override;
};

#endif  // __LOG_H__