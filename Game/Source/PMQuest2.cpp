#include "PMQuest2.h"
#include "App.h"
#include "PlayerModule.h"
#include "InventoryModule.h"

PMQuest2::PMQuest2()
{
	p_QuestId = QuestModule::EQuest::EQUEST_PM_Q2;

	m_KilledBoss = false;

	p_Title = "eye in the sky";
	p_Description = "defeat mipharesh, the first demon king";
}

PMQuest2::~PMQuest2()
{
}

void PMQuest2::UpdateCheck()
{
	
}

bool PMQuest2::HasRequirements()
{
	return m_KilledBoss;
}

void PMQuest2::Finish()
{
	
}

void PMQuest2::OnCharacterKilled(Character::ECharacterType character)
{
	if (character == Character::ECharacterType::ECHARACTER_MIPHARESH) {
		m_KilledBoss = true;
	}
}