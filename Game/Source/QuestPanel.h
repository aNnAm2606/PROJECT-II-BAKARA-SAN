#pragma once
#include "GuiPanel.h"
#include <vector>
#include "Button.h"
#include "Color.h"

class Quest;

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

	void OnEnable() override;

	SDL_Texture* questPanel;
	// Buttons
	GuiButton* closeBtn;
	GuiButton* inventoryBtn;
	GuiButton* partyBtn;
private:
	SDL_Texture* m_ItemsTexture;

	std::vector<Button> m_Buttons;
	std::vector<int> m_QuestIds;
	Quest** m_Quests;

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

	// Left side
	iPoint m_QuestOffset;
	int m_QuestSpacing;
	int m_SelectedQuest;

	// Right side
	iPoint m_QuestInfoOffset;
	iPoint m_QuestRewardsOffset;
	int m_QuestRewardsSpacing;
};