#include "AlanParsons.h"
#include "App.h"
#include "Textures.h"
#include "Fonts.h"

void AlanParsons::FillBaseDialog()
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

	// BRANCH_1
	dnode.text = "well, i guess you opening the door is better than a ghost or a demon doing it, so i can not really be mad at you.";

	id = dialog.AddNode(dnode);

	dnode.text = "oh... it was? damn...";
	dnode.nodes.push_back(id);

	size_t b1 = dialog.AddNode(dnode);

	// BRANCH_2
	dnode.text = "cool!!";

	size_t b2_1_1 = dialog.AddNode(dnode);

	dnode.text = "huh. that is not as cool as a magician.";

	size_t b2_1_2 = dialog.AddNode(dnode);

	dnode.text = "oh... you got my hopes up...";

	size_t b2_1_3 = dialog.AddNode(dnode);

	dnode.text = "woah! you are magicians?";
	dnode.options.push_back("yes");
	dnode.nodes.push_back(b2_1_1);
	dnode.options.push_back("exorcists, technically");
	dnode.nodes.push_back(b2_1_2);
	dnode.options.push_back("sorry, we lied");
	dnode.nodes.push_back(b2_1_3);

	size_t b2_1 = dialog.AddNode(dnode);

	dnode.text = "really?";
	dnode.options.push_back("yes");
	dnode.nodes.push_back(b2_1);
	dnode.options.push_back("no");
	dnode.nodes.push_back(b2_1_3);

	size_t b2 = dialog.AddNode(dnode);

	// BRANCH_3
	dnode.text = "you better do!";

	size_t b3 = dialog.AddNode(dnode);

	// MAIN BRANCH
	dnode.text = "hey! how did you enter the house?";
	dnode.options.push_back("the door was unlocked");
	dnode.nodes.push_back(b1);
	dnode.options.push_back("we used magic to open it");
	dnode.nodes.push_back(b2);
	dnode.options.push_back("sorry, we will leave now.");
	dnode.nodes.push_back(b3);

	id = dialog.AddNode(dnode);

	AddDialog(dialog, id);
}

AlanParsons::AlanParsons()
{
	m_ActiveDialog = 0;
}

AlanParsons::~AlanParsons()
{
}

void AlanParsons::Init()
{
	FillBaseDialog();

	m_NPCTex = app->tex->Load("Assets/Art/NPCs/NPCs.png");
	m_NPCRect = {
		280,25,
		75,85
	};

	m_Position = { 140, 540 };
}
