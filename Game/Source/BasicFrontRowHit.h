#ifndef __BASIC_FRONT_ROW_HIT_H__
#define __BASIC_FRONT_ROW_HIT_H__

#include "Ability.h"

class BasicFrontRowHit : public Ability {
private:

public:
	BasicFrontRowHit(Character* character);
	~BasicFrontRowHit();

	virtual void Execute(iPoint position);
};

#endif  // __ABILITY_H__