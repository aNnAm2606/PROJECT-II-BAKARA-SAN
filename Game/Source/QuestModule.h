#ifndef __QUEST_MODULE_H__
#define __QUEST_MODULE_H__

#include "Module.h"

class Quest;

class QuestModule : public Module
{
public:
	enum EQuest {
		// PRIMUS MUNDIS QUESTS
		EQUEST_PM_Q1,
		EQUEST_PM_Q2,
		EQUEST_PM_Q3,

		// NONE
		EQUEST_NONE
	};

	enum EQuestState {
		EQUEST_STATE_AVAILABLE,
		EQUEST_STATE_ACTIVE,
		EQUEST_STATE_FINISHED,
		EQUEST_STATE_NONE
	};
public:
	QuestModule(bool startEnabled);

	// Destructor
	virtual ~QuestModule();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void ActivateQuest(EQuest quest);

	bool QuestHasRequirements(EQuest quest);
	void FinishQuest(EQuest quet);

	bool FinishedQuest(EQuest quest) { return m_QuestStates[quest] == EQuestState::EQUEST_STATE_FINISHED; }

	bool LoadState(pugi::xml_node& save) override;
	bool SaveState(pugi::xml_node& save) override;
private:
	EQuestState m_QuestStates[EQuest::EQUEST_NONE];
	Quest* m_Quests[EQuest::EQUEST_NONE];
};

#endif // __LOGOSCREEN_H__