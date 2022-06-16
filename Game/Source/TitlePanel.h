#pragma once
#include "GuiPanel.h"
class TitlePanel : public GuiPanel
{

public:
	TitlePanel(bool active);
	~TitlePanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	void OnEnable() override;

	bool OnGuiMouseClickEvent(GuiControl* control) override;

	// Buttons
	GuiButton* startBtn;
	GuiButton* continueBtn;
	GuiButton* settingsBtn;
	GuiButton* creditsBtn;
	GuiButton* quitBtn;

};

