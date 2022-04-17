#ifndef __FALLEN_ANGEL_H__
#define __FALLEN_ANGEL_H__

#include "Enemy.h"

class FallenAngel : public Enemy {
private:

public:
	FallenAngel();
	~FallenAngel();

	void ExecuteAttack();
};

#endif  // __LOG_H__