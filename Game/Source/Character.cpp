#include "Character.h"
#include "App.h"
#include "Render.h"
#include "Ability.h"
#include "App.h"
#include "Textures.h"

Character::Character(iPoint g_pos)
{
	p_GridPosition = g_pos;

	p_IsPlayer = true;
	p_Attacking = false;
	p_Dead = false;
	p_Remove = false;

	p_StatsTexture = app->tex->Load("Assets/Art/GUI/battleUI2.png");
	p_HealthRect = {
		0,
		242,
		119,
		11
	};

	p_HealthMissingRect = {
		0,
		256,
		119,
		11
	};
}

Character::~Character()
{
	for (size_t i = 0; i < p_Abilities.size(); i++) {
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
		p_AttackAnimations[p_SelectedAttack].Update();

		int c_frame = p_AttackAnimations[p_SelectedAttack].GetCurrentFrameCount();

		if (c_frame >= p_Abilities[p_SelectedAttack]->GetStartFrame()) {
			p_Abilities[p_SelectedAttack]->Update();
		}

		if (p_AttackAnimations[p_SelectedAttack].HasFinished()) {
			if (p_Abilities[p_SelectedAttack]->HasFinished()) {
				p_AttackAnimations[p_SelectedAttack].Reset();
				p_Abilities[p_SelectedAttack]->Reset();

				p_Abilities[p_SelectedAttack]->Execute(p_GridPosition);
				p_Attacking = false;
			}
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

	// Character sprites
	if (p_Attacking) {
		SDL_Rect& rect = p_AttackAnimations[0].GetCurrentFrame();

		app->render->DrawTexture(p_CharacterSpriteSheet, position.x, position.y, &rect, false);
	}
	else if (p_Dead) {
		SDL_Rect& rect = p_DeadAnimation.GetCurrentFrame();

		app->render->DrawTexture(p_CharacterSpriteSheet, position.x, position.y, &rect, false);
	}
	else {
		app->render->DrawTexture(p_CharacterSpriteSheet, position.x, position.y, &p_CharacterRect, false);
	}

	// Health bar
	float hperc = p_Stats.health / (float)p_Stats.maxHealth;

	SDL_Rect r = p_HealthRect;
	r.w = p_HealthRect.w * hperc;

	app->render->DrawTexture(p_StatsTexture, position.x, position.y - p_HealthMissingRect.h, &p_HealthMissingRect, false);
	app->render->DrawTextureScaled(p_StatsTexture, position.x, position.y - r.h, r.w * 1.01, r.h, &r, false);
}

void Character::RenderEffects(iPoint position)
{
	if (p_Attacking) {
		if (!p_Abilities[p_SelectedAttack]->HasFinished()) {
			p_Abilities[p_SelectedAttack]->Render(position);
		}
	}
}