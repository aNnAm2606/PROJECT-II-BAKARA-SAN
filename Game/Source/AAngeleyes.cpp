#include "AAngeleyes.h"
#include "App.h"
#include "Render.h"
#include "BattleScene.h"
#include "Character.h"

AAngeleyes::AAngeleyes(Character* character) : Ability(character)
{
	p_Animation.PushBack({ 128 * 4, 0, 128, 128 });
	p_Animation.PushBack({ 128 * 5, 0, 128, 128 });
	p_Animation.speed = 0.1f;
	p_Animation.loop = false;

	p_StartFrame = 0;
}

AAngeleyes::~AAngeleyes()
{
}

void AAngeleyes::Execute(iPoint position)
{
	app->battleScene->AddEnemy(Character::ECharacterType::ECHARACTER_FALLEN_ANGEL, 0, 0);
	app->battleScene->AddEnemy(Character::ECharacterType::ECHARACTER_FALLEN_ANGEL, 0, 1);
}

void AAngeleyes::Render(iPoint position)
{
	
}