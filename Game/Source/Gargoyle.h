#ifndef __GARGOYLE_H__
#define __GARGOYLE_H__

#include "Enemy.h"

class Gargoyle : public Enemy {
private:

public:
	Gargoyle();
	~Gargoyle();

	void ExecuteAttack();
};

#endif  // __LOG_H__