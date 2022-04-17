#include "Paladin.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "BasicFrontRowHit.h"

Paladin::Paladin()
{
	p_CharacterId = ECharacter::ECHARACTER_PALADIN;
	p_Stats.health = 20;
	p_Stats.damage = 1;
	p_Stats.speed = 2;

	p_CharacterSpriteSheet = app->tex->Load("Assets/Art/Characters/paladin.png");
	p_CharacterRect = {
		0, 256,
		128, 128
	};

	p_Abilities[0] = new BasicFrontRowHit(this);
}

Paladin::~Paladin()
{
}

void Paladin::ExecuteAttack()
{
	p_Attacking = true;

	// Attack
	p_Abilities[0]->Execute();

	p_Attacking = false;
}
