#include "Monk.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "ASerpentStrike.h"

Monk::Monk(iPoint g_pos) : Character(g_pos)
{
	p_CharacterId = ECharacterType::ECHARACTER_MONK;
	p_Stats.health = 30;
	p_Stats.maxHealth = 30;
	p_Stats.damage = 30;
	p_Stats.speed = 35;

	p_CharacterSpriteSheet = app->tex->Load("Assets/Art/Characters/monk_battle.png");
	p_CharacterRect = {
		0, 128,
		128, 128
	};

	p_Abilities[0] = new ASerpentStrike(this);

	p_AttackAnimations[0].PushBack({ 0, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 128, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 256, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 128, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 0, 0, 128, 128 });
	p_AttackAnimations[0].speed = 0.2f;
	p_AttackAnimations[0].loop = false;
}

Monk::~Monk()
{
	
}
