#include "ASerpentStrike.h"
#include "App.h"
#include "Render.h"
#include "BattleScene.h"
#include "Character.h"
#include "Audio.h"

ASerpentStrike::ASerpentStrike(Character* character) : Ability(character)
{
	p_AbilityName = "serpent strike";
	p_Animation.PushBack({ 128 * 3, 0, 128, 128 });
	p_Animation.PushBack({ 128 * 4, 0, 128, 128 });
	p_Animation.PushBack({ 128 * 5, 0, 128, 128 });
	p_Animation.speed = 0.1f;
	p_Animation.loop = false;
	p_AbilityFX = app->audio->LoadFx("Assets/Audio/Fx/hit3.wav");
	p_StartFrame = 2;
}

ASerpentStrike::~ASerpentStrike()
{
}

void ASerpentStrike::Execute(iPoint position)
{
	iPoint epos = {
		0,
		position.y
	};
	app->audio->PlayFx(p_AbilityFX);
	app->battleScene->DamageEnemyAt(epos, p_Character->GetDamage());

	epos.x += 1;
	epos.y += 1;
	app->battleScene->DamageEnemyAt(epos, p_Character->GetDamage());
}

void ASerpentStrike::Render(iPoint position)
{
	iPoint epos = {
		position.x + 2*GRID_PIXEL_SIZE,
		position.y
	};

	SDL_Texture* tex = p_Character->GetCharacterSpriteSheet();
	SDL_Rect r = p_Animation.GetCurrentFrame();

	app->render->DrawTexture(tex, epos.x, epos.y, &r, false);

	epos.x += GRID_PIXEL_SIZE;
	epos.y += GRID_PIXEL_SIZE;

	iPoint g_pos = p_Character->GetGridPosition();

	if (g_pos.y < 3) {
		app->render->DrawTexture(tex, epos.x, epos.y, &r, false);
	}
}