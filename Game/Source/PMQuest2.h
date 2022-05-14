#ifndef __PMQUEST2_H__
#define __PMQUEST2_H__

#include "Quest.h"

class PMQuest2 : public Quest {
private:
	bool m_KilledBoss;
public:
	PMQuest2();
	~PMQuest2();

	virtual void UpdateCheck() override;

	virtual bool HasRequirements() override;
	virtual void Finish() override;

	virtual void OnCharacterKilled(Character::ECharacterType character) override;
};

#endif  // __ABILITY_H__