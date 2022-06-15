#ifndef __PMQUEST2_H__
#define __PMQUEST2_H__

#include "Quest.h"

class PMQuest2 : public Quest {
private:
	int m_KillCount;
public:
	PMQuest2();
	~PMQuest2();

	void OnCharacterKilled(Character::ECharacterType character) override;

	void UpdateProgressText() override;
};

#endif  // __ABILITY_H__