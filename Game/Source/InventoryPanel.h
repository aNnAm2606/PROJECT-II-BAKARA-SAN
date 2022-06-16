#pragma once
#include "GuiPanel.h"
#include <vector>
#include "Item.h"
#include "Button.h"

#define ITEMS_PER_ROW 8
#define SPRITESHEET_ITEMS_PER_ROW 6

class InventoryPanel : public GuiPanel
{
private:
	SDL_Texture* m_ItemsTex;
	SDL_Texture* inventoryPanel;

	std::vector<Item::EItemType>* m_Inventory;
	size_t m_InvSize;

	std::vector<Button> m_InventoryButtons;

	void UpdatePanelData();
public:
	InventoryPanel(bool active);
	~InventoryPanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	void OnEnable() override;

	bool OnGuiMouseClickEvent(GuiControl* control) override;

	// Buttons
	GuiButton* closeBtn;
	GuiButton* partyBtn;
	GuiButton* questBtn;

};