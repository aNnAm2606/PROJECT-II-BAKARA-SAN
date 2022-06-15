#ifndef __GARGOYLE_FINAL_BOSS_H__
#define __GARGOYLE_FINAL_BOSS_H__

#include "GargoyleBattle.h"

class Scene;

class GargoyleBattle_FinalBoss : public GargoyleBattle {
public:
	GargoyleBattle_FinalBoss();
	~GargoyleBattle_FinalBoss();

	void SetBattlefield() override;
};

#endif  // __LOG_H__