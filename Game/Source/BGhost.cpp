#include "BGhost.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "ABlackFlame.h"

BGhost::BGhost(iPoint g_pos) : Enemy(g_pos)
{
	p_CharacterName = "spectre";
	p_CharacterId = ECharacterType::ECHARACTER_SPECTRE;
	p_Stats.health = 15;
	p_Stats.maxHealth = 15;
	p_Stats.damage = 15;
	p_Stats.speed = 10;

	p_CharacterSpriteSheet = app->tex->Load("Assets/Art/Enemies/ghost_battle.png");
	p_CharacterRect = {
		0, 0,
		128, 128
	};

	p_Abilities.push_back(new ABlackFlame(this));

	p_AttackAnimations.emplace_back();
	p_AttackAnimations[0].PushBack({ 0, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 128, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 256, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 384, 0, 128, 128 });
	p_AttackAnimations[0].speed = 0.2f;
	p_AttackAnimations[0].loop = false;

	SDL_Rect rect = { 0, 256, 128, 128 };

	for (int i = 0; i < 6; i++) {
		rect.x = i * 128;
		p_DeadAnimation.PushBack(rect);
	}
	p_DeadAnimation.speed = 0.2f;
	p_DeadAnimation.loop = false;
}

BGhost::~BGhost()
{
}