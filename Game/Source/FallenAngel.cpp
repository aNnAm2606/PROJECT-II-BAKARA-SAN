#include "FallenAngel.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "BasicBackRowHit.h"

FallenAngel::FallenAngel()
{
	p_CharacterId = ECharacterType::ECHARACTER_FALLEN_ANGEL;
	p_Stats.health = 20;
	p_Stats.damage = 1;
	p_Stats.speed = 1;

	p_CharacterSpriteSheet = app->tex->Load("Assets/Art/Enemies/fallen_angel.png");
	p_CharacterRect = {
		0, 384,
		128, 128
	};

	p_Abilities[0] = new BasicBackRowHit(this);

	p_AttackAnimations[0].PushBack({ 0, 512, 128, 128 });
	p_AttackAnimations[0].speed = 0.2f;
	p_AttackAnimations[0].loop = false;
}

FallenAngel::~FallenAngel()
{
}
