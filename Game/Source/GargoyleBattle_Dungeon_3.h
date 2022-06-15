#ifndef __GARGOYLE_BATTLE_DUNGEON_3_H__
#define __GARGOYLE_BATTLE_DUNGEON_3_H__

#include "GargoyleBattle.h"

class Scene;

class GargoyleBattle_Dungeon_3 : public GargoyleBattle {
public:
	GargoyleBattle_Dungeon_3();
	~GargoyleBattle_Dungeon_3();

	void SetBattlefield() override;
};

#endif  // __LOG_H__