#include "QuestModule.h"
#include "Dialog.h"

#include "Log.h"

#include "PMQuest1.h"

QuestModule::QuestModule(bool startEnabled) : Module(startEnabled)
{
	name.Create("quests");

	memset(m_QuestStates, EQuestState::EQUEST_STATE_AVAILABLE, EQuest::EQUEST_NONE);
	memset(m_Quests, NULL, EQuest::EQUEST_NONE * sizeof(Quest*));
}

// Destructor
QuestModule::~QuestModule()
{}

// Called before render is available
bool QuestModule::Awake(pugi::xml_node& config)
{
	LOG("Loading QuestModule");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool QuestModule::Start()
{

	return true;
}

// Called each loop iteration
bool QuestModule::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool QuestModule::Update(float dt)
{
	

	return true;
}

// Called each loop iteration
bool QuestModule::PostUpdate()
{
	bool ret = true;


	return ret;
}

// Called before quitting
bool QuestModule::CleanUp()
{
	LOG("Freeing QuestModule");

	return true;
}

void QuestModule::ActivateQuest(EQuest quest)
{
	if (m_QuestStates[quest] == EQuestState::EQUEST_STATE_AVAILABLE) {
		switch (quest) {
			case EQuest::EQUEST_PM_Q1:
				m_Quests[quest] = new PMQuest1();
				break;
		}
	}
}

bool QuestModule::QuestHasRequirements(EQuest quest)
{
	if (m_QuestStates[quest] == EQuestState::EQUEST_STATE_ACTIVE) {
		return m_Quests[quest]->HasRequirements();
	}

	return false;
}

void QuestModule::FinishQuest(EQuest quest)
{
	if (m_QuestStates[quest] == EQuestState::EQUEST_STATE_ACTIVE) {
		if (m_Quests[quest]->HasRequirements()) {
			m_Quests[quest]->Finish();
			delete m_Quests[quest];
			m_Quests[quest] = NULL;

			m_QuestStates[quest] = EQuestState::EQUEST_STATE_FINISHED;
		}
	}
}