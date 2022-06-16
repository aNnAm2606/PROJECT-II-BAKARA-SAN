#ifndef __ASKULL_CRACKER_H__
#define __ASKULL_CRACKER_H__

#include "Ability.h"

class ASkullcracker : public Ability {
private:

public:
	ASkullcracker(Character* character);
	~ASkullcracker();

	void Execute(iPoint position) override;

	void Render(iPoint position) override;

	uint ASkullcracker_FX = NULL;
};

#endif  // __ABILITY_H__