#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "SDL/include/SDL.h"
#include "Point.h"
#include "Animation.h"

#define MAX_ABILITIES 1

struct Stats {
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

		// Enemy characters
		ECHARACTER_FALLEN_ANGEL,
		ECHARACTER_GARGOYLE,

		// None
		ECHARACTERS_NONE
	};
protected:
	Stats p_Stats;
	ECharacterType p_CharacterId;

	SDL_Texture* p_CharacterSpriteSheet;
	SDL_Rect p_CharacterRect;

	Ability* p_Abilities[MAX_ABILITIES];

	Animation p_AttackAnimations[MAX_ABILITIES];
	Animation p_IdleAnimation;

	bool p_IsPlayer;

	bool p_Attacking;
	int p_SelectedAttack;
public:
	Character();
	virtual ~Character();

	int GetDamage() { return p_Stats.damage; }
	void DealDamage(int dmg);

	int GetSpeed() { return p_Stats.speed; }
	int GetHealth() { return p_Stats.health; }
	
	bool IsPlayer() { return p_IsPlayer; }

	void StartAttack(int selectedAttack = -1);
	virtual void Update();

	void Render(iPoint position);

	bool IsAttacking() { return p_Attacking; }
};

#endif  // __LOG_H__