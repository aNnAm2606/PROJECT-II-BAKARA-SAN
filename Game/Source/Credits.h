#pragma once
#include "GuiPanel.h"
class Credits : public GuiPanel
{

public:
	Credits(bool active);
	~Credits();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control) override;

	// Buttons
	GuiButton* closeBtn;
};