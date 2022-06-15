#include "GargoyleBattle_Dungeon_2.h"
#include "App.h"
#include "BattleScene.h"
#include "TownScene.h"

GargoyleBattle_Dungeon_2::GargoyleBattle_Dungeon_2()
{
}

GargoyleBattle_Dungeon_2::~GargoyleBattle_Dungeon_2()
{
}

void GargoyleBattle_Dungeon_2::SetBattlefield()
{
	app->battleScene->SetNextScene(m_OriginScene);
	app->battleScene->AddEnemy(Character::ECharacterType::ECHARACTER_FALLEN_ANGEL, 0, 0);
	app->battleScene->AddEnemy(Character::ECharacterType::ECHARACTER_FALLEN_ANGEL, 1, 1);
}