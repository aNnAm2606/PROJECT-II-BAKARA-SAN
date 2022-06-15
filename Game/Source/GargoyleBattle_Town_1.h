#ifndef __GARGOYLE_BATTLE_TOWN_1_H__
#define __GARGOYLE_BATTLE_TOWN_1_H__

#include "GargoyleBattle.h"

class Scene;

class GargoyleBattle_Town_1 : public GargoyleBattle {
public:
	GargoyleBattle_Town_1();
	~GargoyleBattle_Town_1();

	void SetBattlefield() override;
};

#endif  // __LOG_H__