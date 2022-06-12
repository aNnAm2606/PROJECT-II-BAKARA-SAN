#include "FallenAngel.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "BasicBackRowHit.h"

FallenAngel::FallenAngel()
{
	p_CharacterId = ECharacterType::ECHARACTER_FALLEN_ANGEL;
	p_Stats.health = 20;
	p_Stats.maxHealth = 20;
	p_Stats.damage = 1;
	p_Stats.speed = 1;

	p_CharacterSpriteSheet = app->tex->Load("Assets/Art/Enemies/fallen_angel_battle.png");
	p_CharacterRect = {
		0, 0,
		128, 128
	};

	p_Abilities[0] = new BasicBackRowHit(this);

	p_AttackAnimations[0].PushBack({ 0, 0, 128, 128 });
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

FallenAngel::~FallenAngel()
{
}
