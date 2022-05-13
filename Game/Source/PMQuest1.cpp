#include "PMQuest1.h"
#include "App.h"
#include "PlayerModule.h"
#include "InventoryModule.h"

PMQuest1::PMQuest1()
{
	p_QuestId = QuestModule::EQuest::EQUEST_PM_Q1;

	m_ItemCount = 0;

	p_Title = "Pussy Control";
	p_Description = "Steven�s Cat has gone missing. Find it and bring it to him!";
}

PMQuest1::~PMQuest1()
{
}

void PMQuest1::UpdateCheck()
{
	m_ItemCount = app->inventory->GetItemCount(Item::EItemType::EITEMTYPE_CAT);
}

bool PMQuest1::HasRequirements()
{
	return m_ItemCount >= 1;
}

void PMQuest1::Finish()
{
	app->inventory->RemoveItem(Item::EItemType::EITEMTYPE_CAT);
}

void PMQuest1::OnItemAdd(Item::EItemType item, size_t count)
{
	if (item == Item::EItemType::EITEMTYPE_CAT) {
		m_ItemCount += count;
	}
}

void PMQuest1::OnItemRemove(Item::EItemType item, size_t count)
{
	if (item == Item::EItemType::EITEMTYPE_CAT) {
		m_ItemCount -= count;
	}
}