#include "QuestModule.h"
#include "Dialog.h"

#include "Log.h"

// All quests
#include "PMQuest1.h"
#include "PMQuest2.h"

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
			case EQuest::EQUEST_PM_Q2:
				m_Quests[quest] = new PMQuest2();
				break;
		}

		m_Quests[quest]->UpdateCheck();
		m_QuestStates[quest] = EQuestState::EQUEST_STATE_ACTIVE;

		std::cout << "[Quest] Activated quest: [" << m_Quests[quest]->getTitle() << "] : [" << m_Quests[quest]->getDesc() << "]" << std::endl;
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

			std::cout << "[Quest] Finished quest: [" << m_Quests[quest]->getTitle() << "] : [" << m_Quests[quest]->getDesc() << "]" << std::endl;

			delete m_Quests[quest];
			m_Quests[quest] = NULL;

			m_QuestStates[quest] = EQuestState::EQUEST_STATE_FINISHED;
		}
	}
}

bool QuestModule::LoadState(pugi::xml_node& save)
{
	pugi::xml_node quest = save.first_child();

	for (int i = 0; i < EQUEST_NONE; i++) {
		EQuestState state = (EQuestState)quest.attribute("state").as_int();

		if (state == EQuestState::EQUEST_STATE_ACTIVE) {
			if (!m_Quests[i]) {
				ActivateQuest((EQuest)i);
			}
		}

		m_QuestStates[i] = state;

		quest = quest.next_sibling();
	}

	return true;
}

bool QuestModule::SaveState(pugi::xml_node& save)
{
	for (int i = 0; i < EQUEST_NONE; i++) {
		pugi::xml_node quest = save.append_child("quest");

		quest.append_attribute("id") = i;
		quest.append_attribute("state") = m_QuestStates[i];
	}

	return true;
}
