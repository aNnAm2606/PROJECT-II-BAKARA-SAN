#include "Cat.h"
#include "App.h"
#include "Textures.h"
#include "Fonts.h"
#include "FadeToBlack.h"
#include "TutorialScene_4.h"
#include "BattleScene.h"
#include "InventoryModule.h"

Cat::Cat()
{
	
}

Cat::~Cat()
{
}

void Cat::Init()
{
	m_NPCTex = app->tex->Load("Assets/Art/NPCs/cat.png");
	m_NPCRect = {
		0, 0,
		128, 128
	};

	m_Position = { 1560, 240 };
}

void Cat::OnUpdate()
{
	if (app->quests->FinishedQuest(QuestModule::EQuest::EQUEST_PM_Q1)) {
		m_Active = false;
	}
}

void Cat::OnInteract()
{
	app->inventory->AddItem(Item::EItemType::EITEMTYPE_CAT);
	m_Active = false;
}