#include "Quest.h"
#include "App.h"
#include "InventoryModule.h"

Quest::Quest()
{
	p_QuestId = QuestModule::EQuest::EQUEST_NONE;

	app->inventory->questOnAddCallbacks += QuestItemAction(&Quest::OnItemAdd, this);
	app->inventory->questOnRemoveCallbacks += QuestItemAction(&Quest::OnItemRemove, this);

	UpdateCheck();
}

Quest::~Quest()
{
	app->inventory->questOnAddCallbacks -= QuestItemAction(&Quest::OnItemAdd, this);
	app->inventory->questOnRemoveCallbacks -= QuestItemAction(&Quest::OnItemRemove, this);
}