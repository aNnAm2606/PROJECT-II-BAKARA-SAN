#include "Character.h"
#include "App.h"
#include "Render.h"

Character::Character()
{
	p_IsPlayer = true;
	p_Attacking = false;
}

Character::~Character()
{
	for (int i = 0; i < MAX_ABILITIES; i++) {
		delete p_Abilities[i];
	}
}

void Character::DealDamage(int dmg)
{
	p_Stats.health -= dmg;
}

void Character::Render(iPoint position)
{
	app->render->DrawTexture(p_CharacterSpriteSheet, position.x, position.y, &p_CharacterRect);
}