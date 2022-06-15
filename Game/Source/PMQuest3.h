#ifndef __PMQUEST3_H__
#define __PMQUEST3_H__

#include "Quest.h"

class PMQuest3 : public Quest {
private:
	size_t m_KillCount;
public:
	PMQuest3();
	~PMQuest3();

	bool HasRequirements() override;

	void UpdateProgressText() override;

	void OnGameSave(pugi::xml_node& quest) override;
	void OnGameLoad(pugi::xml_node& quest) override;

	void OnCharacterKilled(Character::ECharacterType character) override;
};

#endif  // __ABILITY_H__