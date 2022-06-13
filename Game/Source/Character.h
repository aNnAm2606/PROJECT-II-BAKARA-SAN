#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "SDL/include/SDL.h"
#include "Point.h"
#include "Animation.h"

#include <string>
#include <vector>

struct Stats {
	int maxHealth;
	int health;
	int damage;
	int speed;
};

class Ability;

class Character {
public:
	enum class ECharacterType {
		// Player characters
		ECHARACTER_CHAMAN,
		ECHARACTER_PALADIN,
		ECHARACTER_MONK,

		// Enemy characters
		ECHARACTER_FALLEN_ANGEL,
		ECHARACTER_GARGOYLE,
		ECHARACTER_GHOST,
		ECHARACTER_MIPHARESH,
		ECHARACTER_SPECTRE,

		// None
		ECHARACTERS_NONE
	};
protected:
	Stats p_Stats;
	ECharacterType p_CharacterId;

	SDL_Texture* p_StatsTexture;
	SDL_Rect p_HealthRect;
	SDL_Rect p_HealthMissingRect;

	SDL_Texture* p_CharacterSpriteSheet;
	SDL_Rect p_CharacterRect;

	std::vector<Ability*> p_Abilities;

	std::vector<Animation> p_AttackAnimations;
	Animation p_IdleAnimation;
	Animation p_DeadAnimation;

	iPoint p_GridPosition;

	bool p_IsPlayer;

	bool p_Attacking;
	bool p_Dead;
	bool p_Remove;
	int p_SelectedAttack;

	std::string p_CharacterName;
public:
	Character(iPoint g_pos);
	virtual ~Character();

	int GetDamage() { return p_Stats.damage; }
	bool DealDamage(int dmg);

	int GetSpeed() { return p_Stats.speed; }
	int GetHealth() { return p_Stats.health; }
	int GetMaxHealth() { return p_Stats.maxHealth; }
	
	bool IsPlayer() { return p_IsPlayer; }

	void StartAttack(int selectedAttack = 0);
	virtual void Update();

	void Render(iPoint position);
	void RenderEffects(iPoint position);

	bool IsAttacking() { return p_Attacking; }

	bool IsDead() { return p_Dead; }
	bool Remove() { return p_Remove; }

	void SetGridPosition(iPoint position) { p_GridPosition = position; }
	iPoint GetGridPosition() { return p_GridPosition; }

	ECharacterType getCharacterType() { return p_CharacterId; }

	SDL_Texture* GetCharacterSpriteSheet() { return p_CharacterSpriteSheet; }

	std::vector<Ability*>* GetAbilities() { return &p_Abilities; }

	const char* GetCharacterName() { return p_CharacterName.c_str(); }
};

#endif  // __LOG_H__