#include "GargoyleBattle_FinalBoss.h"
#include "App.h"
#include "BattleScene.h"
#include "EndScreen.h"

GargoyleBattle_FinalBoss::GargoyleBattle_FinalBoss()
{
}

GargoyleBattle_FinalBoss::~GargoyleBattle_FinalBoss()
{
}

void GargoyleBattle_FinalBoss::SetBattlefield()
{
	app->battleScene->SetNextScene(app->endScreen);
	app->battleScene->AddEnemy(Character::ECharacterType::ECHARACTER_MIPHARESH, 1, 1);
}