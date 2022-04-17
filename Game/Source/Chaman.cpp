#include "Chaman.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "BasicBackRowHit.h"

Chaman::Chaman()
{
	p_CharacterId = ECharacter::ECHARACTER_CHAMAN;
	p_Stats.health = 20;
	p_Stats.damage = 1;
	p_Stats.speed = 2;

	p_CharacterSpriteSheet = app->tex->Load("Assets/Art/Characters/chaman.png");
	p_CharacterRect = {
		0, 256,
		128, 128
	};

	p_Abilities[0] = new BasicBackRowHit(this);
}

Chaman::~Chaman()
{
	
}

void Chaman::ExecuteAttack()
{
	p_Attacking = true;
	p_Abilities[0]->Execute();
	p_Attacking = false;
}
