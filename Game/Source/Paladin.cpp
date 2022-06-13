#include "Paladin.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "ASkullcracker.h"

Paladin::Paladin(iPoint g_pos) : Character(g_pos)
{
	p_CharacterName = "Agnetha";
	p_CharacterId = ECharacterType::ECHARACTER_PALADIN;
	p_Stats.health = 50;
	p_Stats.maxHealth = 50;
	p_Stats.damage = 20;
	p_Stats.speed = 10;

	p_CharacterSpriteSheet = app->tex->Load("Assets/Art/Characters/paladin_battle.png");
	p_CharacterRect = {
		0, 128,
		128, 128
	};

	p_Abilities.push_back(new ASkullcracker(this));

	p_AttackAnimations.emplace_back();
	p_AttackAnimations[0].PushBack({ 0, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 128, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 256, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 128, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 0, 0, 128, 128 });
	p_AttackAnimations[0].speed = 0.2f;
	p_AttackAnimations[0].loop = false;
}

Paladin::~Paladin()
{
}
