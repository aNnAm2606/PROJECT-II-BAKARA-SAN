#ifndef __ASACRED_FLAME_H__
#define __ASACRED_FLAME_H__

#include "Ability.h"

class ASacredFlame : public Ability {
private:

public:
	ASacredFlame(Character* character);
	~ASacredFlame();

	void Execute(iPoint position) override;

	void Render(iPoint position) override;
};

#endif  // __ABILITY_H__