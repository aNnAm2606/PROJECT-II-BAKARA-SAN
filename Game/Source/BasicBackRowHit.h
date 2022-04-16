#ifndef __BASIC_BACK_ROW_HIT_H__
#define __BASIC_BACK_ROW_HIT_H__

#include "Ability.h"

class BasicBackRowHit : public Ability {
private:

public:
	BasicBackRowHit(Character* character);
	~BasicBackRowHit();

	virtual void Execute();
};

#endif  // __ABILITY_H__