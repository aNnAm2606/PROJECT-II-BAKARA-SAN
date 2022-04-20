#pragma once
#include "GuiPanel.h"
class BattlePanel : public GuiPanel
{

public:
	BattlePanel(bool active);
	~BattlePanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control) override;

	// Buttons
	GuiButton* ChamanBtn;
	GuiButton* PaladinBtn;
	GuiButton* attackBtn;
	GuiButton* dodgeBtn;
	GuiButton* runBtn;
	GuiButton* fallenAngelBtn;
	GuiButton* ghostBtn;
	GuiButton* gargoyleBtn;

	// Box texture
	SDL_Rect charBox;
	SDL_Rect actionBox;
	SDL_Rect enemyBox;
	SDL_Rect arrow;

	// Arrow for selecting
	int charArrow = -1;
	int actionArrow = -1;
	int enemyArrow = -1;
};
