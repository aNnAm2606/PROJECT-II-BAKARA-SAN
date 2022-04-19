#pragma once
#include "GuiPanel.h"
class pausePanel : public GuiPanel
{

public:
	pausePanel(bool active);
	~pausePanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control) override;

	// Buttons
	GuiButton* closeBtn;
};

