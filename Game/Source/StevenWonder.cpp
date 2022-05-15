#include "StevenWonder.h"
#include "App.h"
#include "Textures.h"
#include "Fonts.h"
#include "InventoryModule.h"
#include "QuestModule.h"

void StevenWonder::FillBaseDialog()
{
	SDL_Texture* dialogImg = app->tex->Load("Assets/Art/Dialogs/dialog_box.png");

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	int font = app->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);

	Dialog dialog;
	dialog.SetPosition(414, 220);
	dialog.SetDialogBg(dialogImg, 453, 206);
	dialog.SetFont(font);
	dialog.SetNPC(this);

	// FILL
	DialogNode dnode;
	size_t id;

	// YES
	dnode.text = "i can not thank you enough! take this as compensation!";

	id = dialog.AddNode(dnode);
	
	dnode.text = "great! where is he?";
	dnode.options.push_back("here you go!");
	dnode.nodes.push_back(id);
	dnode.optionsData.push_back(1);

	size_t mission_completed = dialog.AddNode(dnode);

	dnode.text = "damn.";

	id = dialog.AddNode(dnode);

	dnode.text = "great! where is he?";
	dnode.options.push_back("sorry, i lied");
	dnode.nodes.push_back(id);

	size_t mission_uncompleted = dialog.AddNode(dnode);

	// NO
	dnode.text = "thanks.";

	size_t b_no_1 = dialog.AddNode(dnode);

	dnode.text = "hmm... i last saw	him in the northern	beach, but i am too much of a coward to go there again!";

	size_t b_no_2 = dialog.AddNode(dnode);

	dnode.text = "oh... if you see him let me know...";
	dnode.options.push_back("i will!");
	dnode.nodes.push_back(b_no_1);
	dnode.options.push_back("where did you last see him?");
	dnode.nodes.push_back(b_no_2);

	size_t b_no = dialog.AddNode(dnode);

	// MAIN
	dnode.text = "hey you! have you seen my cat?";
	dnode.options.push_back("yes!");
	dnode.nodes.push_back(-1);
	dnode.options.push_back("no.");
	dnode.nodes.push_back(b_no);

	size_t mission_box = dialog.AddNode(dnode);

	dnode.text = "yuuusuuuuf!!! yuuuuusuuuuuuuuf!!!!";
	dnode.nodes.push_back(mission_box);

	id = dialog.AddNode(dnode);

	AddDialog(dialog, id);

	m_MissionBoxId = mission_box;
	m_CompletedId = mission_completed;
	m_UncompletedId = mission_uncompleted;
}

void StevenWonder::FillCompletedDialog()
{
	SDL_Texture* dialogImg = app->tex->Load("Assets/Art/Dialogs/dialog_box.png");

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	int font = app->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);

	Dialog dialog;
	dialog.SetPosition(414, 220);
	dialog.SetDialogBg(dialogImg, 453, 206);
	dialog.SetFont(font);
	dialog.SetNPC(this);

	// FILL
	DialogNode dnode;
	size_t id;

	dnode.text = "i am a furry!";

	id = dialog.AddNode(dnode);

	dnode.text = "now i will be able to have fun with yusuf again!";
	dnode.nodes.push_back(id);

	id = dialog.AddNode(dnode);

	AddDialog(dialog, id);
}

StevenWonder::StevenWonder()
{
	m_ActiveDialog = ESTEVENDIALOG_MAIN;
	m_GiveCat = false;
}

StevenWonder::~StevenWonder()
{
}

void StevenWonder::Init()
{
	FillBaseDialog();
	FillCompletedDialog();

	m_NPCTex = app->tex->Load("Assets/Art/NPCs/NPCs.png");
	m_NPCRect = {
		280,25,
		75,85
	};

	m_Position = { 600, 650 };
}

void StevenWonder::OnUpdate()
{
	if (app->quests->FinishedQuest(QuestModule::EQuest::EQUEST_PM_Q1)) {
		m_ActiveDialog = EStevenDialog::ESTEVENDIALOG_COMPLETED;
	}
}

void StevenWonder::OnDialogStart()
{
	app->quests->ActivateQuest(QuestModule::EQuest::EQUEST_PM_Q1);

	if (app->quests->QuestHasRequirements(QuestModule::EQuest::EQUEST_PM_Q1)) {
		m_Dialogs[EStevenDialog::ESTEVENDIALOG_MAIN].SetFollowNode(m_MissionBoxId, 0, m_CompletedId);
	}
	else {
		m_Dialogs[EStevenDialog::ESTEVENDIALOG_MAIN].SetFollowNode(m_MissionBoxId, 0, m_UncompletedId);
	}
}

void StevenWonder::OnDialogFinish()
{
	if (m_GiveCat) {
		app->quests->FinishQuest(QuestModule::EQuest::EQUEST_PM_Q1);

		m_GiveCat = false;

		m_ActiveDialog = EStevenDialog::ESTEVENDIALOG_COMPLETED;
	}
}

void StevenWonder::OnDialogButton(size_t data)
{
	m_GiveCat = true;
}