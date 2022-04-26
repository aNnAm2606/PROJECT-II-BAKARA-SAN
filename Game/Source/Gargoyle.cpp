#include "Gargoyle.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "BasicFrontRowHit.h"

Gargoyle::Gargoyle()
{
	p_CharacterId = ECharacterType::ECHARACTER_GARGOYLE;
	p_Stats.health = 20;
	p_Stats.damage = 1;
	p_Stats.speed = 1;

	p_CharacterSpriteSheet = app->tex->Load("Assets/Art/Enemies/gargoyle.png");
	p_CharacterRect = {
		0, 256,
		128, 128
	};

	p_Abilities[0] = new BasicFrontRowHit(this);

	p_AttackAnimations[0].PushBack({ 0, 384, 128, 128 });
	p_AttackAnimations[0].PushBack({ 128, 384, 128, 128 });
	p_AttackAnimations[0].PushBack({ 256, 384, 128, 128 });
	p_AttackAnimations[0].speed = 0.2f;
	p_AttackAnimations[0].loop = false;
}

Gargoyle::~Gargoyle()
{
}