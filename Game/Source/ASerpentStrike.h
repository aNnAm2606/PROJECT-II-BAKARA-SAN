#ifndef __ASERPENT_STRIKE_H__
#define __ASERPENT_STRIKE_H__

#include "Ability.h"

class ASerpentStrike : public Ability {
private:

public:
	ASerpentStrike(Character* character);
	~ASerpentStrike();

	void Execute(iPoint position) override;

	void Render(iPoint position) override;
};

#endif  // __ABILITY_H__