#include "ASkullcracker.h"
#include "App.h"
#include "Render.h"
#include "BattleScene.h"
#include "Character.h"

ASkullcracker::ASkullcracker(Character* character) : Ability(character)
{
	p_AbilityName = "Skullcracker";
	p_Animation.PushBack({ 128 * 3, 0, 128, 128 });
	p_Animation.PushBack({ 128 * 4, 0, 128, 128 });
	p_Animation.speed = 0.1f;
	p_Animation.loop = false;

	p_StartFrame = 2;
}

ASkullcracker::~ASkullcracker()
{
}

void ASkullcracker::Execute(iPoint position)
{
	iPoint epos = {
		0,
		position.y
	};

	app->battleScene->DamageEnemyAt(epos, p_Character->GetDamage());
}

void ASkullcracker::Render(iPoint position)
{
	iPoint epos = {
		position.x + 2*GRID_PIXEL_SIZE,
		position.y
	};

	SDL_Texture* tex = p_Character->GetCharacterSpriteSheet();
	SDL_Rect r = p_Animation.GetCurrentFrame();

	app->render->DrawTexture(tex, epos.x, epos.y, &r);
}