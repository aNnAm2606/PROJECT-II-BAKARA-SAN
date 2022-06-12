#include "ASlash.h"
#include "App.h"
#include "Render.h"
#include "BattleScene.h"
#include "Character.h"

ASlash::ASlash(Character* character) : Ability(character)
{
	p_Animation.PushBack({ 128 * 4, 0, 128, 128 });
	p_Animation.PushBack({ 128 * 5, 0, 128, 128 });
	p_Animation.PushBack({ 128 * 6, 0, 128, 128 });
	p_Animation.speed = 0.1f;
	p_Animation.loop = false;

	p_StartFrame = 2;
}

ASlash::~ASlash()
{
}

void ASlash::Execute(iPoint position)
{
	iPoint epos = {
		1,
		position.y
	};

	app->battleScene->DamagePlayerAt(epos, p_Character->GetDamage());
}

void ASlash::Render(iPoint position)
{
	iPoint epos = {
		position.x - 2*GRID_PIXEL_SIZE,
		position.y
	};

	SDL_Texture* tex = p_Character->GetCharacterSpriteSheet();
	SDL_Rect r = p_Animation.GetCurrentFrame();

	app->render->DrawTexture(tex, epos.x, epos.y, &r);
}