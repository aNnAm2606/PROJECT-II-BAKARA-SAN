#include "ASacredFlame.h"
#include "App.h"
#include "Render.h"
#include "BattleScene.h"
#include "Character.h"
#include "Audio.h"

ASacredFlame::ASacredFlame(Character* character) : Ability(character)
{
	p_AbilityName = "sacred flame";
	p_Animation.PushBack({ 128 * 3, 0, 128, 128 });
	p_Animation.PushBack({ 128 * 4, 0, 128, 128 });
	p_Animation.PushBack({ 128 * 5, 0, 128, 128 });
	p_Animation.PushBack({ 128 * 6, 0, 128, 128 });
	p_Animation.speed = 0.1f;
	p_Animation.loop = false;
	p_AbilityFX = app->audio->LoadFx("Assets/Audio/Fx/hit1.wav");
	p_StartFrame = 2;
}

ASacredFlame::~ASacredFlame()
{
}

void ASacredFlame::Execute(iPoint position)
{
	iPoint epos = {
		1,
		position.y
	};
	app->audio->PlayFx(p_AbilityFX);
	app->battleScene->DamageEnemyAt(epos, p_Character->GetDamage());
}

void ASacredFlame::Render(iPoint position)
{
	iPoint epos = {
		position.x + 4*GRID_PIXEL_SIZE,
		position.y
	};

	SDL_Texture* tex = p_Character->GetCharacterSpriteSheet();
	SDL_Rect r = p_Animation.GetCurrentFrame();

	app->render->DrawTexture(tex, epos.x, epos.y, &r, false);
}