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
};

