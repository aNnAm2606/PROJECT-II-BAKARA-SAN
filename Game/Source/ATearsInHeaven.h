#ifndef __ATEARS_IN_HEAVEN_H__
#define __ATEARS_IN_HEAVEN_H__

#include "Ability.h"

class ATearsInHeaven : public Ability {
private:

public:
	ATearsInHeaven(Character* character);
	~ATearsInHeaven();

	void Execute(iPoint position) override;

	void Render(iPoint position) override;
};

#endif  // __ABILITY_H__