#include "ATearsInHeaven.h"
#include "App.h"
#include "Render.h"
#include "BattleScene.h"
#include "Character.h"
#include "Audio.h"

ATearsInHeaven::ATearsInHeaven(Character* character) : Ability(character)
{
	p_Animation.PushBack({ 128 * 1, 0, 128, 128 });
	p_Animation.PushBack({ 128 * 2, 0, 128, 128 });
	p_Animation.PushBack({ 128 * 3, 0, 128, 128 });
	p_Animation.PushBack({ 128 * 4, 0, 128, 128 }); 
	p_Animation.speed = 0.1f;
	p_Animation.loop = false;
	p_AbilityFX = app->audio->LoadFx("Assets/Audio/Fx/hit3.wav");
	p_StartFrame = 0;
}

ATearsInHeaven::~ATearsInHeaven()
{
}

void ATearsInHeaven::Execute(iPoint position)
{
	iPoint epos = {
		0,
		position.y
	};
	app->audio->PlayFx(p_AbilityFX);
	app->battleScene->DamagePlayerAt(epos, p_Character->GetDamage());

	epos.x = 1;
	app->battleScene->DamagePlayerAt(epos, p_Character->GetDamage());
}

void ATearsInHeaven::Render(iPoint position)
{
	iPoint epos = {
		position.x - 4*GRID_PIXEL_SIZE,
		position.y
	};

	SDL_Texture* tex = p_Character->GetCharacterSpriteSheet();
	SDL_Rect r = p_Animation.GetCurrentFrame();

	app->render->DrawTexture(tex, epos.x, epos.y, &r);
	app->render->DrawTexture(tex, epos.x + GRID_PIXEL_SIZE, epos.y, &r, false);
}