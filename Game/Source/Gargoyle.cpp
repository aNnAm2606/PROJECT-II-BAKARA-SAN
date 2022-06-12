#include "Gargoyle.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "ASlash.h"

Gargoyle::Gargoyle(iPoint g_pos) : Enemy(g_pos)
{
	p_CharacterId = ECharacterType::ECHARACTER_GARGOYLE;
	p_Stats.health = 20;
	p_Stats.maxHealth = 20;
	p_Stats.damage = 10;
	p_Stats.speed = 20;

	p_CharacterSpriteSheet = app->tex->Load("Assets/Art/Enemies/gargoyle_battle.png");
	p_CharacterRect = {
		0, 0,
		128, 128
	};

	p_Abilities[0] = new ASlash(this);

	p_AttackAnimations[0].PushBack({ 0, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 128, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 256, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 384, 0, 128, 128 });
	p_AttackAnimations[0].speed = 0.2f;
	p_AttackAnimations[0].loop = false;

	SDL_Rect rect = { 0, 256, 128, 128 };

	for (int i = 0; i < 5; i++) {
		rect.x = i * 128;
		p_DeadAnimation.PushBack(rect);
	}
	p_DeadAnimation.speed = 0.2f;
	p_DeadAnimation.loop = false;
}

Gargoyle::~Gargoyle()
{
}