#include "StevenWonder.h"
#include "App.h"
#include "Textures.h"
#include "Fonts.h"

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

	id = dialog.AddNode(dnode);

	dnode.text = "yuuusuuuuf!!! yuuuuusuuuuuuuuf!!!!";
	dnode.nodes.push_back(id);

	id = dialog.AddNode(dnode);

	AddDialog(dialog, id);
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
	m_ActiveDialog = 0;
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

	m_Position = { 905, 320 };
}
