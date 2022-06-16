#pragma once
#include "GuiPanel.h"
#include "Color.h"
#include <vector>

class Character;
class Ability;

class PartyPanel : public GuiPanel
{

public:
	PartyPanel(bool active);
	~PartyPanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control) override;

	// Buttons
	GuiButton* closeBtn;
	GuiButton* inventoryBtn;
	GuiButton* questBtn;
	GuiButton* Btn1;
	GuiButton* Btn2;
	GuiButton* Btn3;
	GuiButton* Btn4;

	// chars
	SDL_Texture* chamanStats;
	SDL_Texture* chamanPic;
	SDL_Texture* paladinStats;
	SDL_Texture* paladinPic;
	SDL_Texture* monkStats;
	SDL_Texture* monkPic;
	SDL_Texture* priestStats;
	SDL_Texture* priestPic;
	SDL_Texture* partyPanel;

private:
	uint swidth, sheight;

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

	int selected = 0;
};

