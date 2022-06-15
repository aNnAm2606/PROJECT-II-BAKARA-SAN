#include "PMQuest1.h"
#include "App.h"
#include "PlayerModule.h"
#include "InventoryModule.h"

PMQuest1::PMQuest1()
{
	p_QuestId = QuestModule::EQuest::EQUEST_PM_Q1;

	m_ItemCount = 0;

	p_Title = "pussy control";
	p_Description = "stevens cat has gone missing. find it and bring it to him!";

	p_Rewards[0] = Item::EItemType::EITEMTYPE_CYAN_POTION_SMALL;
}

PMQuest1::~PMQuest1()
{
}

void PMQuest1::UpdateCheck()
{
	m_ItemCount = app->inventory->GetItemCount(Item::EItemType::EITEMTYPE_CAT);

	UpdateProgressText();
}

void PMQuest1::UpdateProgressText()
{
	m_ProgressText.clear();

	m_ProgressText += std::to_string(m_ItemCount);
	m_ProgressText += " / 1";
}

bool PMQuest1::HasRequirements()
{
	return m_ItemCount >= 1;
}

void PMQuest1::OnFinish()
{
	app->inventory->RemoveItem(Item::EItemType::EITEMTYPE_CAT);
}

void PMQuest1::OnItemAdd(Item::EItemType item, size_t count)
{
	if (item == Item::EItemType::EITEMTYPE_CAT) {
		m_ItemCount += count;

		UpdateProgressText();
	}
}

void PMQuest1::OnItemRemove(Item::EItemType item, size_t count)
{
	if (item == Item::EItemType::EITEMTYPE_CAT) {
		m_ItemCount -= count;

		UpdateProgressText();
	}
}