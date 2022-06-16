#include "Priest.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "ASacredFlame.h"
#include "Audio.h"

Priest::Priest(iPoint g_pos) : Character(g_pos)
{
	p_CharacterName = "Gabriel";
	p_CharacterId = ECharacterType::ECHARACTER_PRIEST;
	p_Stats.health = 30;
	p_Stats.maxHealth = 30;
	p_Stats.damage = 20;
	p_Stats.speed = 20;
	p_CharacterFX = app->audio->LoadFx("Assets/Audio/Fx/dead6.wav");

	p_CharacterSpriteSheet = app->tex->Load("Assets/Art/Characters/priest_battle.png");
	p_CharacterRect = {
		0, 0,
		128, 128
	};

	p_Abilities.push_back(new ASacredFlame(this));

	p_AttackAnimations.emplace_back();
	p_AttackAnimations[0].PushBack({ 0, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 128, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 256, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 128, 0, 128, 128 });
	p_AttackAnimations[0].PushBack({ 0, 0, 128, 128 });
	p_AttackAnimations[0].speed = 0.2f;
	p_AttackAnimations[0].loop = false;
}

Priest::~Priest()
{
	
}
