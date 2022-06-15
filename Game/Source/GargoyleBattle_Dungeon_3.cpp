#include "GargoyleBattle_Dungeon_3.h"
#include "App.h"
#include "BattleScene.h"
#include "TownScene.h"

GargoyleBattle_Dungeon_3::GargoyleBattle_Dungeon_3()
{
}

GargoyleBattle_Dungeon_3::~GargoyleBattle_Dungeon_3()
{
}

void GargoyleBattle_Dungeon_3::SetBattlefield()
{
	app->battleScene->SetNextScene(m_OriginScene);
	app->battleScene->AddEnemy(Character::ECharacterType::ECHARACTER_GARGOYLE, 0, 0);
	app->battleScene->AddEnemy(Character::ECharacterType::ECHARACTER_GARGOYLE, 0, 1);
}