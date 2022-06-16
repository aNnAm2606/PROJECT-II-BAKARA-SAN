#pragma once
#include "GuiPanel.h"
class SettingsPanel : public GuiPanel
{

public:
	SettingsPanel(bool active);
	~SettingsPanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	void OnEnable() override;

	bool OnGuiMouseClickEvent(GuiControl* control) override;

	// Buttons
	GuiToggle* fullSrnON;
	GuiToggle* fullSrnOff;
	GuiToggle* vsyncOn;
	GuiToggle* vsyncOff;
	GuiButton* quitBtn;
	GuiButton* saveBtn;
	GuiButton* resetBtn;
	GuiButton* returnbtn;
	GuiSlider* volumeSldr;
	GuiSlider* musicSldr;
	GuiSlider* fxSldr;

	SDL_Rect box;

	bool fullscreen = false;
	bool vsync = false;
};

