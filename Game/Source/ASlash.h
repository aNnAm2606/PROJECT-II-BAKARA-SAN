#ifndef __ASLASH_H__
#define __ASLASH_H__

#include "Ability.h"

class ASlash : public Ability {
private:

public:
	ASlash(Character* character);
	~ASlash();

	void Execute(iPoint position) override;

	void Render(iPoint position) override;
};

#endif  // __ABILITY_H__