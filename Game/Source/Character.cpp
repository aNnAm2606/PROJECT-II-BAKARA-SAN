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

		int c_frame = p_AttackAnimations[0].GetCurrentFrameCount();

		if (c_frame >= p_Abilities[0]->GetStartFrame()) {
			p_Abilities[0]->Update();
		}

		if (p_AttackAnimations[0].HasFinished()) {
			if (p_Abilities[0]->HasFinished()) {
				p_AttackAnimations[0].Reset();
				p_Abilities[0]->Reset();

				p_Abilities[0]->Execute(p_GridPosition);
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

		app->render->DrawTexture(p_CharacterSpriteSheet, position.x, position.y, &rect);
	}
	else if (p_Dead) {
		SDL_Rect& rect = p_DeadAnimation.GetCurrentFrame();

		app->render->DrawTexture(p_CharacterSpriteSheet, position.x, position.y, &rect);
	}
	else {
		app->render->DrawTexture(p_CharacterSpriteSheet, position.x, position.y, &p_CharacterRect);
	}

	// Health bar
	float hperc = p_Stats.health / (float)p_Stats.maxHealth;

	SDL_Rect r = p_HealthRect;
	r.w = p_HealthRect.w * hperc;

	app->render->DrawTexture(p_StatsTexture, position.x, position.y - p_HealthMissingRect.h, &p_HealthMissingRect);
	app->render->DrawTextureScaled(p_StatsTexture, position.x, position.y - r.h, r.w * 1.01, r.h, &r);
}

void Character::RenderEffects(iPoint position)
{
	if (p_Attacking) {
		if (!p_Abilities[0]->HasFinished()) {
			p_Abilities[0]->Render(position);
		}
	}
}