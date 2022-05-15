#pragma once
#include "GuiPanel.h"

#define ITEMS_PER_ROW 8
#define SPRITESHEET_ITEMS_PER_ROW 6

class InventoryPanel : public GuiPanel
{
private:
	SDL_Texture* m_ItemsTex;
public:
	InventoryPanel(bool active);
	~InventoryPanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control) override;

	// Buttons
	GuiButton* closeBtn;
};

