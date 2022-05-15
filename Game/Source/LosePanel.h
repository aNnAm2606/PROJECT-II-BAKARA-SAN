#pragma once
#include "GuiPanel.h"
class LosePanel : public GuiPanel
{

public:
	LosePanel(bool active);
	~LosePanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control) override;

	// Buttons
	GuiButton* closeBtn;
};

