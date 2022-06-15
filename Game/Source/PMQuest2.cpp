#include "PMQuest2.h"
#include "App.h"
#include "PlayerModule.h"
#include "InventoryModule.h"

PMQuest2::PMQuest2()
{
	p_QuestId = QuestModule::EQuest::EQUEST_PM_Q2;

	p_Title = "eye in the sky";
	p_Description = "defeat mipharesh, the first demon king";

	UpdateProgressText();
}

PMQuest2::~PMQuest2()
{
}

void PMQuest2::OnCharacterKilled(Character::ECharacterType character)
{
	if (character == Character::ECharacterType::ECHARACTER_MIPHARESH) {
		m_KillCount++;
		app->quests->FinishQuest(p_QuestId);

		UpdateProgressText();
	}
}

void PMQuest2::UpdateProgressText()
{
	m_ProgressText.clear();

	m_ProgressText += std::to_string(m_KillCount);
	m_ProgressText += " / 1";
}