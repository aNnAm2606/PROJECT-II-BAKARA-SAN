#include "BasicFrontRowHit.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "BattleScene.h"

BasicFrontRowHit::BasicFrontRowHit(Character* character) : Ability(character)
{
	
}

BasicFrontRowHit::~BasicFrontRowHit()
{
}

void BasicFrontRowHit::Execute()
{
	iPoint position;
	
	if (p_Character->IsPlayer()) {
		position.x = 0;
		for (int y = 0; y < GRID_HEIGHT; y++) {
			position.y = y;
			app->battleScene->DamageEnemyAt(position, p_Character->GetDamage());
		}
	}
	else {
		position.x = 1;
		for (int y = 0; y < GRID_HEIGHT; y++) {
			position.y = y;
			app->battleScene->DamagePlayerAt(position, p_Character->GetDamage());
		}
	}
}