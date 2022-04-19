#pragma once
#include "GuiPanel.h"
class QuitPanel : public GuiPanel
{

public:
	QuitPanel(bool active);
	~QuitPanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control) override;

	// Buttons
	GuiButton* yesBtn;
	GuiButton* noBtn;

	// Box texture
	SDL_Rect box;
};

