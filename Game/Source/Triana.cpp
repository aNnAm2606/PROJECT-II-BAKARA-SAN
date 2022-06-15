#include "Triana.h"
#include "App.h"
#include "Textures.h"
#include "Fonts.h"
#include "Audio.h"


void Triana::FillShopDialog()
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
	dnode.text = "i am triana, the greatest shopkeeper in town! mainly because i am the only one open. he he he!";
	dnode.nodes.push_back(-1);

	size_t talk_b1 = dialog.AddNode(dnode);

	// TALK_B2
	dnode.text = "ah, primundians... always thinking they're the center of the world...";
	dnode.nodes.push_back(-1);

	size_t talk_b2_back = dialog.AddNode(dnode);

	dnode.text = "the four kingdoms are not the center of the world, you know?";
	dnode.options.push_back("they are not?");
	dnode.nodes.push_back(talk_b2_back);

	id = dialog.AddNode(dnode);

	dnode.text = "oh, you have picked up on my accent, eh? i was born in a distant peninsula, practically in the opposite side of the world.";
	dnode.nodes.push_back(id);

	size_t talk_b2 = dialog.AddNode(dnode);

	// TALK_B3_1
	dnode.text = "i do not know what you have been drinking, but i would like some of that!";
	dnode.nodes.push_back(-1);

	size_t talk_b3_back1 = dialog.AddNode(dnode);

	dnode.text = "let me tell you something, if you are going to prank somebody you should think these things through beforehand...";
	dnode.nodes.push_back(-1);

	size_t talk_b3_back2 = dialog.AddNode(dnode);

	dnode.text = "yeah, sure. i guess a bunch of red guys with tridents are roaming the streets this very instant, right?";
	dnode.options.push_back("yes!");
	dnode.nodes.push_back(talk_b3_back1);
	dnode.options.push_back("not exactly...");
	dnode.nodes.push_back(talk_b3_back2);

	size_t talk_b3_1 = dialog.AddNode(dnode);

	// TALK_B3_2
	dnode.text = "well... you look like a bunch of hippies, but you do not see me complaining!";
	dnode.nodes.push_back(-1);

	size_t talk_b3_back3 = dialog.AddNode(dnode);

	// TALK_B3_3
	dnode.text = "well, if you say so!";
	dnode.nodes.push_back(-1);

	size_t talk_b3_back4 = dialog.AddNode(dnode);

	// TALK_B3
	dnode.text = "huh? why would I be hurt, miarma?";
	dnode.options.push_back("there is a fleet of demons attacking us!");
	dnode.nodes.push_back(talk_b3_1);
	dnode.options.push_back("because you look awful!");
	dnode.nodes.push_back(talk_b3_back3);
	dnode.options.push_back("oh, forget about it.");
	dnode.nodes.push_back(talk_b3_back4);

	size_t talk_b3 = dialog.AddNode(dnode);

	// MAIN_TALK
	dnode.text = "sure thing, miarma! what do you want to know?";
	dnode.options.push_back("who are you?");
	dnode.nodes.push_back(talk_b1);
	dnode.options.push_back("are you from around here?");
	dnode.nodes.push_back(talk_b2);
	dnode.options.push_back("are you hurt?");
	dnode.nodes.push_back(talk_b3);
	dnode.options.push_back("nevermind...");
	dnode.nodes.push_back(-1);

	size_t main_talk = dialog.AddNode(dnode);
	dialog.SetFollowNode(talk_b1, 0, main_talk);
	dialog.SetFollowNode(talk_b2_back, 0, main_talk);
	dialog.SetFollowNode(talk_b3_back1, 0, main_talk);
	dialog.SetFollowNode(talk_b3_back2, 0, main_talk);
	dialog.SetFollowNode(talk_b3_back3, 0, main_talk);
	dialog.SetFollowNode(talk_b3_back4, 0, main_talk);
	
	// MAIN_BUY
	dnode.text = "whoops! looks like i am a bit low on stock. sorry about that";
	dnode.nodes.push_back(-1);

	size_t main_buy = dialog.AddNode(dnode);

	// MAIN_SELL
	dnode.text = "hmmm... you do not have a lot i can buy...";
	dnode.nodes.push_back(-1);

	size_t main_sell = dialog.AddNode(dnode);

	// MAIN_EXIT
	dnode.text = "may the holy one guide your path.";

	id = dialog.AddNode(dnode);

	// MAIN
	dnode.text = "what are you looking for?";
	dnode.options.push_back("buy");
	dnode.nodes.push_back(main_buy);
	dnode.options.push_back("sell");
	dnode.nodes.push_back(main_sell);
	dnode.options.push_back("talk");
	dnode.nodes.push_back(main_talk);
	dnode.options.push_back("exit");
	dnode.nodes.push_back(id);

	id = dialog.AddNode(dnode);
	dialog.SetFollowNode(main_buy, 0, id);
	dialog.SetFollowNode(main_sell, 0, id);
	dialog.SetFollowNode(main_talk, 3, id);

	dialog.SetActiveNode(id);

	AddDialog(dialog, id);
}

Triana::Triana()
{
	m_ActiveDialog = 0;
}

Triana::~Triana()
{
}

void Triana::OnInit()
{
	FillShopDialog();

	m_NPCTex = app->tex->Load("Assets/Art/NPCs/NPCs.png");
	m_NPCFX = app->audio->LoadFx("Assets/Audio/Fx/NPC5.wav");
	m_NPCRect = {
		25, 25,
		75, 85
	};

	m_Position = { 1185, 650 };
}
