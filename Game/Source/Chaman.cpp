#include "Chaman.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "AShadowBolt.h"
#include "Audio.h"

Chaman::Chaman(iPoint g_pos) : Character(g_pos)
{
	p_CharacterName = "chaka";
	p_CharacterId = ECharacterType::ECHARACTER_CHAMAN;
	p_Stats.health = 20;
	p_Stats.maxHealth = 20;
	p_Stats.damage = 35;
	p_Stats.speed = 20;
	p_CharacterFX = app->audio->LoadFx("Assets/Audio/Fx/dead7.wav");

	p_CharacterSpriteSheet = app->tex->Load("Assets/Art/Characters/chaman_battle.png");
	p_CharacterRect = {
		0, 128,
		128, 128
	};

	p_Abilities.push_back(new AShadowBolt(this));

	p_AttackAnimations.emplace_back();
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
