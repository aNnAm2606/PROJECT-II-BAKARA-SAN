#include "PMQuest3.h"
#include "App.h"
#include "PlayerModule.h"
#include "InventoryModule.h"
#include <string>

PMQuest3::PMQuest3()
{
	p_QuestId = QuestModule::EQuest::EQUEST_PM_Q3;

	m_KillCount = false;

	p_Title = "scary monsters";
	p_Description = "defeat 5 spectre.";
}

PMQuest3::~PMQuest3()
{
}

bool PMQuest3::HasRequirements()
{
	return m_KillCount >= 5;
}

void PMQuest3::UpdateProgressText()
{
	m_ProgressText.clear();
	m_ProgressText += std::to_string(m_KillCount);
	m_ProgressText += " / 5";
}

void PMQuest3::OnGameSave(pugi::xml_node& quest)
{
	quest.append_attribute("data") = m_KillCount;
}

void PMQuest3::OnGameLoad(pugi::xml_node& quest)
{
	m_KillCount = quest.attribute("data").as_int();

	UpdateProgressText();
}

void PMQuest3::OnCharacterKilled(Character::ECharacterType character)
{
	if (character == Character::ECharacterType::ECHARACTER_SPECTRE) {
		m_KillCount++;

		UpdateProgressText();
	}
}