#include "Gargoyle.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "BasicFrontRowHit.h"

Gargoyle::Gargoyle()
{
	p_CharacterId = ECharacter::ECHARACTER_GARGOYLE;
	p_Stats.health = 20;
	p_Stats.damage = 1;
	p_Stats.speed = 1;

	p_CharacterSpriteSheet = app->tex->Load("Assets/Art/Enemies/gargoyle.png");
	p_CharacterRect = {
		0, 256,
		128, 128
	};

	p_Abilities[0] = new BasicFrontRowHit(this);
}

Gargoyle::~Gargoyle()
{
}

void Gargoyle::ExecuteAttack()
{
	p_Attacking = true;
	p_Abilities[0]->Execute();
	p_Attacking = false;
}
