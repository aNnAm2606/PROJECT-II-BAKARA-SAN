#ifndef __ABLACK_FLAME_H__
#define __ABLACK_FLAME_H__

#include "Ability.h"

class ABlackFlame : public Ability {
private:

public:
	ABlackFlame(Character* character);
	~ABlackFlame();

	void Execute(iPoint position) override;

	void Render(iPoint position) override;
};

#endif  // __ABILITY_H__