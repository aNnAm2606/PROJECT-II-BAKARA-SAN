#ifndef __AANGELEYES_H__
#define __AANGELEYES_H__

#include "Ability.h"

class AAngeleyes : public Ability {
private:

public:
	AAngeleyes(Character* character);
	~AAngeleyes();

	void Execute(iPoint position) override;

	void Render(iPoint position) override;
};

#endif  // __ABILITY_H__