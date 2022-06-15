#include "DavidBow.h"
#include "App.h"
#include "Textures.h"
#include "Fonts.h"
#include "InventoryModule.h"
#include "QuestModule.h"
#include "Audio.h"


void DavidBow::FillBaseDialog()
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

	// MAIN
	dnode.text = "i knew you were heroes! i need you to kill five spectres for me. pretty please!";
	
	size_t b_yes = dialog.AddNode(dnode);

	dnode.text = "well... i appear to have misjudged you";

	size_t b_no = dialog.AddNode(dnode);

	dnode.text = "you guys look like heroes! could you do me a favor?";
	dnode.options.push_back("sure!");
	dnode.nodes.push_back(b_yes);
	dnode.optionsData.push_back(1);
	dnode.options.push_back("no.");
	dnode.nodes.push_back(b_no);

	id = dialog.AddNode(dnode);

	AddDialog(dialog, id);
}

void DavidBow::FillCompletedDialog()
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

	dnode.text = "hahahahahahahahahahahaha hahahahahahahaha";

	id = dialog.AddNode(dnode);

	dnode.text = "thank you very much! those spectres deserved pain!";
	dnode.nodes.push_back(id);

	id = dialog.AddNode(dnode);

	AddDialog(dialog, id);
}

DavidBow::DavidBow()
{
	m_ActiveDialog = EDAVIDDIALOG_MAIN;
}

DavidBow::~DavidBow()
{
}

void DavidBow::Init()
{
	FillBaseDialog();
	FillCompletedDialog();

	m_NPCTex = app->tex->Load("Assets/Art/NPCs/NPCs.png");
	m_NPCFX = app->audio->LoadFx("Assets/Audio/Fx/NPC2.wav");
	m_NPCRect = {
		280,25,
		75,85
	};

	m_Position = { 230, 230 };
}

void DavidBow::OnUpdate()
{
	if (app->quests->QuestHasRequirements(QuestModule::EQuest::EQUEST_PM_Q3)) {
		m_ActiveDialog = EDAVIDDIALOG_COMPLETED;
	}
}

void DavidBow::OnDialogStart()
{
	
}

void DavidBow::OnDialogFinish()
{
	if (!app->quests->FinishedQuest(QuestModule::EQuest::EQUEST_PM_Q3)) {
		app->quests->FinishQuest(QuestModule::EQuest::EQUEST_PM_Q3);
	}
}

void DavidBow::OnDialogButton(size_t data)
{
	if (data == 1) {
		app->quests->ActivateQuest(QuestModule::EQuest::EQUEST_PM_Q3);
	}
}