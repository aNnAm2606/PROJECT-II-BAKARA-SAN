#pragma once
#include "GuiPanel.h"
class PartyPanel : public GuiPanel
{

public:
	PartyPanel(bool active);
	~PartyPanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control) override;

	// Buttons
	GuiButton* closeBtn;

	// chars
	SDL_Texture* chamanStats;
	SDL_Texture* chamanPic;
	SDL_Texture* paladinStats;
	SDL_Texture* paladinPic;
	SDL_Texture* monkStats;
	SDL_Texture* monkPic;
	SDL_Texture* priestStats;
	SDL_Texture* priestPic;

	int selected = 0;
};

