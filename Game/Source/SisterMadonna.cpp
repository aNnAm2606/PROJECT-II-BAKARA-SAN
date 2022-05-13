#include "SisterMadonna.h"
#include "App.h"
#include "Textures.h"
#include "Fonts.h"

void SisterMadonna::FillBaseDialog()
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

	// TALK_B1
	dnode.text = "it is a process where the soul is returned to its original state. when a soul is purified, you get healed and you gain your mp back...";
	dnode.nodes.push_back(-1);

	size_t talk_b1_back = dialog.AddNode(dnode);

	dnode.text = "sigh";
	dnode.nodes.push_back(talk_b1_back);

	size_t talk_b1_b1 = dialog.AddNode(dnode);

	dnode.text = "i am sister madonna... i am the temporary head of this sanctuary... i am here basically just in case someone needs purifying...";
	dnode.options.push_back("what is purifying");
	dnode.nodes.push_back(talk_b1_b1);
	dnode.options.push_back("nevermind.");
	dnode.nodes.push_back(-1);

	size_t talk_b1 = dialog.AddNode(dnode);

	// TALK_B2
	dnode.text = "sigh";
	dnode.nodes.push_back(-1);

	size_t talk_b2_back = dialog.AddNode(dnode);

	dnode.text = "i will go prepare the tombstones...";
	dnode.nodes.push_back(-1);

	size_t talk_b2_back2 = dialog.AddNode(dnode);

	dnode.text = "well... more or less... this whole apocalypse thing has me feeling a bit down.";
	dnode.options.push_back("that is an expected reaction, i guess");
	dnode.nodes.push_back(talk_b2_back);
	dnode.options.push_back("do not worry, we will defeat all of the demons!");
	dnode.nodes.push_back(talk_b2_back2);

	size_t talk_b2 = dialog.AddNode(dnode);

	// TALK_B3
	dnode.text = "not really... i mostly just sit down and stare at that wall... it is pretty relaxing actually...";
	dnode.nodes.push_back(-1);

	size_t talk_b3_back = dialog.AddNode(dnode);

	dnode.text = "they are probably dead.";
	dnode.options.push_back("oh.");
	dnode.nodes.push_back(-1);

	size_t talk_b3_b2_b1_back = dialog.AddNode(dnode);

	dnode.text = "there needed to be someone here to perform the purifications. since i am the youngest sister i had to stay here.";
	dnode.nodes.push_back(-1);

	size_t talk_b3_b2_b2_back = dialog.AddNode(dnode);

	dnode.text = "they went to exorcise some demons, and meanwhile they have left me here.";
	dnode.options.push_back("do you think they are alright?");
	dnode.nodes.push_back(talk_b3_b2_b1_back);
	dnode.options.push_back("why would they leave you here alone?");
	dnode.nodes.push_back(talk_b3_b2_b2_back);

	size_t talk_b3_b1_b2 = dialog.AddNode(dnode);

	dnode.text = "i guess...";
	dnode.options.push_back("is it a hard job?");
	dnode.nodes.push_back(talk_b3_back);
	dnode.options.push_back("where are the other nuns?");
	dnode.nodes.push_back(talk_b3_b1_b2);

	size_t talk_b3_b1 = dialog.AddNode(dnode);

	dnode.text = "please stay away from me.";

	size_t talk_b3_b2 = dialog.AddNode(dnode);

	dnode.text = "yes...";
	dnode.options.push_back("cool!");
	dnode.nodes.push_back(talk_b3_b1);
	dnode.options.push_back("hot!");
	dnode.nodes.push_back(talk_b3_b2);

	size_t talk_b3 = dialog.AddNode(dnode);

	// TALK_B4
	dnode.text = "oh... okay... goodbye then...";

	size_t talk_b4 = dialog.AddNode(dnode);

	// TALK
	dnode.text = "wh...what do you want to talk about?";
	dnode.options.push_back("who are you?");
	dnode.nodes.push_back(talk_b1);
	dnode.options.push_back("are you... okay?");
	dnode.nodes.push_back(talk_b2);
	dnode.options.push_back("you are a nun!");
	dnode.nodes.push_back(talk_b3);
	dnode.options.push_back("goodbye.");
	dnode.nodes.push_back(talk_b4);

	size_t b_talk = dialog.AddNode(dnode);
	dialog.SetFollowNode(talk_b1_back, 0, b_talk);
	dialog.SetFollowNode(talk_b1, 1, b_talk);
	dialog.SetFollowNode(talk_b2_back, 0, b_talk);
	dialog.SetFollowNode(talk_b2_back2, 0, b_talk);
	dialog.SetFollowNode(talk_b3_back, 0, b_talk);
	dialog.SetFollowNode(talk_b3_b2_b1_back, 0, b_talk);
	dialog.SetFollowNode(talk_b3_b2_b2_back, 0, b_talk);

	// PURIFY
	dnode.text = "that is it... try not to die... i guess...";
	
	id = dialog.AddNode(dnode);

	dnode.text = "okay... hold on a minute...";
	dnode.options.push_back("heal hp and mp");
	dnode.nodes.push_back(id);

	size_t b_purify = dialog.AddNode(dnode);

	// MAIN BRANCH
	dnode.text = "oh... hello... what d-do you need?";
	dnode.options.push_back("purify");
	dnode.nodes.push_back(b_purify);
	dnode.optionsData.push_back(-1);
	dnode.options.push_back("talk");
	dnode.nodes.push_back(b_talk);
	dnode.optionsData.push_back(27);

	id = dialog.AddNode(dnode);

	AddDialog(dialog, id);
}

SisterMadonna::SisterMadonna()
{
	m_ActiveDialog = 0;
}

SisterMadonna::~SisterMadonna()
{
}

void SisterMadonna::OnDialogButton(size_t data)
{
	std::cout << data << std::endl;
}

void SisterMadonna::Init()
{
	FillBaseDialog();

	m_NPCTex = app->tex->Load("Assets/Art/NPCs/NPCs.png");
	m_NPCRect = {
		160, 25,
		60, 80
	};

	m_Position = { 805, 320 };
}
