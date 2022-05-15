#include "PMQuest3.h"
#include "App.h"
#include "PlayerModule.h"
#include "InventoryModule.h"

PMQuest3::PMQuest3()
{
	p_QuestId = QuestModule::EQuest::EQUEST_PM_Q2;

	m_KillCount = false;

	p_Title = "scary monsters";
	p_Description = "defeat 5 spectre.";
}

PMQuest3::~PMQuest3()
{
}

void PMQuest3::UpdateCheck()
{
	
}

bool PMQuest3::HasRequirements()
{
	return m_KillCount >= 5;
}

void PMQuest3::Finish()
{
	
}

void PMQuest3::OnGameSave(pugi::xml_node& quest)
{
	quest.append_attribute("data") = m_KillCount;
}

void PMQuest3::OnGameLoad(pugi::xml_node& quest)
{
	m_KillCount = quest.attribute("data").as_int();
}

void PMQuest3::OnCharacterKilled(Character::ECharacterType character)
{
	if (character == Character::ECharacterType::ECHARACTER_SPECTRE) {
		m_KillCount++;
	}
}