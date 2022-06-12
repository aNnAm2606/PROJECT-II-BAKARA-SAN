#ifndef __ASHADOW_BOLT_H__
#define __ASHADOW_BOLT_H__

#include "Ability.h"

class AShadowBolt : public Ability {
private:

public:
	AShadowBolt(Character* character);
	~AShadowBolt();

	void Execute(iPoint position) override;

	void Render(iPoint position) override;
};

#endif  // __ABILITY_H__