#pragma once
#include "GuiPanel.h"
#include "Button.h"
#include "Color.h"

#include <vector>

class Character;
class Ability;

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

	void OnEnable() override;
	void OnDisable() override;
private:
	uint swidth, sheight;

	Character* character;
	std::vector<Ability*>* abilities;

	// Attack buttons
	std::vector<Button> m_Buttons;

	// Box texture
	SDL_Rect big_box;
	SDL_Rect medium_box;
	SDL_Rect small_box;
	SDL_Rect arrow;

	// Colors
	Color m_LabelColor;
	Color m_BaseColor;
	Color m_HighlightColor;
	Color m_PressColor;

	// Fonts
	int m_LabelFont;
	int m_BaseFont;
	int m_HighlightFont;
	int m_PressFont;
};
