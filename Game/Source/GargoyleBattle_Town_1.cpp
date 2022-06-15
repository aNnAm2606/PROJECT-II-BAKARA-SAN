#include "GargoyleBattle_Town_1.h"
#include "App.h"
#include "BattleScene.h"
#include "TownScene.h"

GargoyleBattle_Town_1::GargoyleBattle_Town_1()
{
}

GargoyleBattle_Town_1::~GargoyleBattle_Town_1()
{
}

void GargoyleBattle_Town_1::SetBattlefield()
{
	app->battleScene->SetNextScene(app->townScene);
	app->battleScene->AddEnemy(Character::ECharacterType::ECHARACTER_FALLEN_ANGEL, 0, 0);
	app->battleScene->AddEnemy(Character::ECharacterType::ECHARACTER_GARGOYLE, 0, 1);
	app->battleScene->AddEnemy(Character::ECharacterType::ECHARACTER_SPECTRE, 1, 1);
	app->battleScene->AddEnemy(Character::ECharacterType::ECHARACTER_SPECTRE, 1, 2);
	app->battleScene->AddEnemy(Character::ECharacterType::ECHARACTER_SPECTRE, 1, 3);
}