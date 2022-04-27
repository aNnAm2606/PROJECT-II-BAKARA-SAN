#include "Character.h"
#include "App.h"
#include "Render.h"
#include "Ability.h"

Character::Character()
{
	p_IsPlayer = true;
	p_Attacking = false;
	p_Dead = false;
	p_Remove = false;
}

Character::~Character()
{
	for (int i = 0; i < MAX_ABILITIES; i++) {
		delete p_Abilities[i];
	}
}

bool Character::DealDamage(int dmg)
{
	p_Stats.health -= dmg;

	if (p_Stats.health <= 0) {
		p_Dead = true;
	}

	return p_Dead;
}

void Character::StartAttack(int selectedAttack)
{
	p_Attacking = true;
	p_SelectedAttack = selectedAttack;
}

void Character::Update()
{
	if (p_Remove) return;

	// TODO: Use selected attack
	if (p_Attacking) {
		p_AttackAnimations[0].Update();

		if (p_AttackAnimations[0].HasFinished()) {
			p_AttackAnimations[0].Reset();
			p_Abilities[0]->Execute();
			p_Attacking = false;
		}
	}

	if (p_Dead) {
		p_DeadAnimation.Update();

		if (p_DeadAnimation.HasFinished()) {
			p_Remove = true;
		}
	}
}

void Character::Render(iPoint position)
{
	if (p_Remove) return;

	if (p_Attacking) {
		SDL_Rect& rect = p_AttackAnimations[0].GetCurrentFrame();

		app->render->DrawTexture(p_CharacterSpriteSheet, position.x, position.y, &rect);
		
	}
	else if (p_Dead) {
		SDL_Rect& rect = p_DeadAnimation.GetCurrentFrame();

		app->render->DrawTexture(p_CharacterSpriteSheet, position.x, position.y, &rect);
	}
	else {
		app->render->DrawTexture(p_CharacterSpriteSheet, position.x, position.y, &p_CharacterRect);
	}
}