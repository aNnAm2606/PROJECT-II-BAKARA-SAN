#include "Character.h"
#include "App.h"
#include "Render.h"
#include "Ability.h"

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

void Character::StartAttack(int selectedAttack)
{
	p_Attacking = true;
	p_SelectedAttack = selectedAttack;
}

void Character::Update()
{
	// TODO: Use selected attack
	if (p_Attacking) {
		p_AttackAnimations[0].Update();

		if (p_AttackAnimations[0].HasFinished()) {
			p_AttackAnimations[0].Reset();
			p_Abilities[0]->Execute();
			p_Attacking = false;
		}
	}
}

void Character::Render(iPoint position)
{
	if (!p_Attacking) {
		app->render->DrawTexture(p_CharacterSpriteSheet, position.x, position.y, &p_CharacterRect);
	}
	else {
		SDL_Rect& rect = p_AttackAnimations[0].GetCurrentFrame();

		app->render->DrawTexture(p_CharacterSpriteSheet, position.x, position.y, &rect);
	}
}