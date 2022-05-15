#include "Paladin.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "BasicFrontRowHit.h"

Paladin::Paladin()
{
	p_CharacterId = ECharacterType::ECHARACTER_PALADIN;
	p_Stats.health = 30;
	p_Stats.damage = 4;
	p_Stats.speed = 2;

	p_CharacterSpriteSheet = app->tex->Load("Assets/Art/Characters/paladin_battle.png");
	p_CharacterRect = {
		0, 128,
		128, 128
	};

	p_Abilities[0] = new BasicFrontRowHit(this);

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
