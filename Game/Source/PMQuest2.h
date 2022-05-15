#ifndef __PMQUEST2_H__
#define __PMQUEST2_H__

#include "Quest.h"

class PMQuest2 : public Quest {
private:

public:
	PMQuest2();
	~PMQuest2();

	void OnCharacterKilled(Character::ECharacterType character) override;
};

#endif  // __ABILITY_H__