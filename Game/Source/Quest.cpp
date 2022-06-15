#include "Quest.h"
#include "App.h"
#include "InventoryModule.h"
#include "BattleScene.h"

Quest::Quest()
{
	p_QuestId = QuestModule::EQuest::EQUEST_NONE;

	app->inventory->questOnAddCallbacks += QuestItemAction(&Quest::OnItemAdd, this);
	app->inventory->questOnRemoveCallbacks += QuestItemAction(&Quest::OnItemRemove, this);

	app->battleScene->onCharacterKilled += QuestCharacterAction(&Quest::OnCharacterKilled, this);

	for (int i = 0; i < 4; i++) {
		p_Rewards[i] = Item::EItemType::EITEMTYPE_NONE;
	}
}

Quest::~Quest()
{
	app->inventory->questOnAddCallbacks -= QuestItemAction(&Quest::OnItemAdd, this);
	app->inventory->questOnRemoveCallbacks -= QuestItemAction(&Quest::OnItemRemove, this);

	app->battleScene->onCharacterKilled -= QuestCharacterAction(&Quest::OnCharacterKilled, this);
}

void Quest::Finish()
{
	for (int i = 0; i < 4; i++) {
		Item::EItemType item = p_Rewards[i];

		if (item != Item::EItemType::EITEMTYPE_NONE) {
			app->inventory->AddItem(item);
		}
	}

	OnFinish();
}