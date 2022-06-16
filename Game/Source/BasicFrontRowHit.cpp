#include "BasicFrontRowHit.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "BattleScene.h"
#include "Audio.h"

BasicFrontRowHit::BasicFrontRowHit(Character* character) : Ability(character)
{
	p_Animation.loop = false;
	p_AbilityFX = app->audio->LoadFx("Assets/Audio/Fx/hit2.wav");
}

BasicFrontRowHit::~BasicFrontRowHit()
{
}

void BasicFrontRowHit::Execute(iPoint p)
{
	iPoint position;
	app->audio->PlayFx(p_AbilityFX);
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