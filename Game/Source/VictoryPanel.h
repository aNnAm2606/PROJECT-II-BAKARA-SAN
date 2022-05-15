#pragma once
#include "GuiPanel.h"
class VictoryPanel : public GuiPanel
{

public:
	VictoryPanel(bool active);
	~VictoryPanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control) override;

	// Buttons
	GuiButton* closeBtn;
};

