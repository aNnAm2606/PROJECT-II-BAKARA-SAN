#include "InventoryPanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "TitleScreen.h"
#include "InventoryModule.h"
#include "Textures.h"

InventoryPanel::InventoryPanel(bool active) : GuiPanel(active)
{
    Active = active;
}

InventoryPanel::~InventoryPanel()
{
}

bool InventoryPanel::Start()
{
    m_ItemsTex = app->tex->Load("Assets/Art/Items/items.png");

    return true;
}

bool InventoryPanel::Update(float dt, bool doLogic)
{
    GuiPanel::Update(dt, doLogic);
    return true;
}

bool InventoryPanel::Draw()
{
    app->render->DrawTexture(app->guiManager->inventoryScreen, 0, 0, NULL, false);

    std::vector<Item::EItemType>* inventory = app->inventory->GetInventory();
    size_t size = inventory->size();

    SDL_Rect itemrect = {
        0, 0,
        34, 34
    };

    iPoint ipos = { 105, 160 };

    size_t spacing = 28;

    int dWidth = 88;
    int dHeight = 88;

    for (size_t i = 0; i < size; i++) {
        size_t xind = i % ITEMS_PER_ROW;
        size_t yind = i / ITEMS_PER_ROW;

        int drawX = ipos.x + xind * dWidth + xind * spacing;
        int drawY = ipos.y + yind * dHeight + yind * spacing;

        itemrect.x = (inventory->at(i) % SPRITESHEET_ITEMS_PER_ROW) * itemrect.w;
        itemrect.y = (inventory->at(i) / SPRITESHEET_ITEMS_PER_ROW) * itemrect.h;

        app->render->DrawTextureScaled(m_ItemsTex, drawX, drawY, dWidth, dHeight, &itemrect, false);
    }

    GuiPanel::Draw();
    return true;
}

bool InventoryPanel::CleanUp()
{
    app->guiManager->inventoryPanel->Disable();
    return true;
}

bool InventoryPanel::OnGuiMouseClickEvent(GuiControl* control)
{

    return true;
}
