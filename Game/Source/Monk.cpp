#include "Monk.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "ASerpentStrike.h"
#include "Audio.h"

Monk::Monk(iPoint g_pos) : Character(g_pos)
{
	p_CharacterName = "matsubara";
	p_CharacterId = ECharacterType::ECHARACTER_MONK;
	p_Stats.health = 30;
	p_Stats.maxHealth = 30;
	p_Stats.damage = 30;
	p_Stats.speed = 35;
	p_CharacterFX = app->audio->LoadFx("Assets/Audio/Fx/dead8.wav");

	p_CharacterSpriteSheet = app->tex->Load("Assets/Art/Characters/monk_battle.png");
	p_CharacterRect = {
		0, 128,
		128, 128
	};

	p_Abilities.push_back(new ASerpentStrike(this));

	p_AttackAnimations.emplace_back();
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
