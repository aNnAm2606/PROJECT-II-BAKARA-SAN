#include "GargoyleBattle_Dungeon_4.h"
#include "App.h"
#include "BattleScene.h"
#include "TownScene.h"

GargoyleBattle_Dungeon_4::GargoyleBattle_Dungeon_4()
{
}

GargoyleBattle_Dungeon_4::~GargoyleBattle_Dungeon_4()
{
}

void GargoyleBattle_Dungeon_4::SetBattlefield()
{
	app->battleScene->SetNextScene(m_OriginScene);
	app->battleScene->AddEnemy(Character::ECharacterType::ECHARACTER_GARGOYLE, 0, 0);
	app->battleScene->AddEnemy(Character::ECharacterType::ECHARACTER_GARGOYLE, 0, 1);
	app->battleScene->AddEnemy(Character::ECharacterType::ECHARACTER_FALLEN_ANGEL, 1, 1);
	app->battleScene->AddEnemy(Character::ECharacterType::ECHARACTER_SPECTRE, 1, 2);
}