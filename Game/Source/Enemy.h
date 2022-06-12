#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Character.h"

class Enemy : public Character {
private:

public:
	Enemy(iPoint g_pos);
	virtual ~Enemy();
};

#endif  // __LOG_H__