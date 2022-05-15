#pragma once
#include "GuiPanel.h"
class QuestPanel : public GuiPanel
{

public:
	QuestPanel(bool active);
	~QuestPanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control) override;

	// Buttons
	GuiButton* closeBtn;
};

