#include "Chaman.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "AShadowBolt.h"

Chaman::Chaman(iPoint g_pos) : Character(g_pos)
{
	p_CharacterId = ECharacterType::ECHARACTER_CHAMAN;
	p_Stats.health = 20;
	p_Stats.maxHealth = 20;
	p_Stats.damage = 35;
	p_Stats.speed = 20;

	p_CharacterSpriteSheet = app->tex->Load("Assets/Art/Characters/chaman_battle.png");
	p_CharacterRect = {
		0, 128,
		128, 128
	};

	p_Abilities[0] = new AShadowBolt(this);

	p_AttackAnimations[0].PushBack({ 0, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 128, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 256, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 128, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 0, 0, 128, 128 });
	p_AttackAnimations[0].speed = 0.2f;
	p_AttackAnimations[0].loop = false;
}

Chaman::~Chaman()
{
	
}
