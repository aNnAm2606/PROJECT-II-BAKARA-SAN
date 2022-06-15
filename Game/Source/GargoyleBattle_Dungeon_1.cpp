#include "GargoyleBattle_Dungeon_1.h"
#include "App.h"
#include "BattleScene.h"
#include "TownScene.h"

GargoyleBattle_Dungeon_1::GargoyleBattle_Dungeon_1()
{
}

GargoyleBattle_Dungeon_1::~GargoyleBattle_Dungeon_1()
{
}

void GargoyleBattle_Dungeon_1::SetBattlefield()
{
	app->battleScene->SetNextScene(m_OriginScene);
	app->battleScene->AddEnemy(Character::ECharacterType::ECHARACTER_SPECTRE, 0, 1);
}