#include "InventoryPanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "TitleScreen.h"
#include "InventoryModule.h"
#include "Textures.h"
#include "Transitions.h"

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
    inventoryPanel = app->tex->Load("Assets/Art/GUI/inventoryUI.png");

    partyBtn = (GuiButton*)CreateGuiButton(0, app->guiManager, this, { 1001,58,126,58 }, "party");
    partyBtn->texture = app->guiManager->titleButtons;
    partyBtn->normalRec = { 1001,58,126,58 };
    partyBtn->focusedRec = { 1001,58,126,58 };
    partyBtn->pressedRec = { 1001,58,126,58 };

    questBtn = (GuiButton*)CreateGuiButton(1, app->guiManager, this, { 1128,58,124,58 }, "quest");
    questBtn->texture = app->guiManager->titleButtons;
    questBtn->normalRec = { 1128,58,124,58 };
    questBtn->focusedRec = { 1128,58,124,58 };
    questBtn->pressedRec = { 1128,58,124,58 };

    return true;
}

bool InventoryPanel::Update(float dt, bool doLogic)
{
    GuiPanel::Update(dt, doLogic);
    return true;
}

bool InventoryPanel::Draw()
{
    if (app->guiManager->cursorMode == true)
    {
        switch (app->guiManager->anim)
        {
        case 0:
            app->render->DrawTexture(inventoryPanel, 603, 352, &app->guiManager->rect1,false);
            break;
        case 1:
            app->render->DrawTexture(inventoryPanel, 587, 326, &app->guiManager->rect2, false);
            break;
        case 2:
            app->render->DrawTexture(inventoryPanel, 560, 307, &app->guiManager->rect3, false);
            break;
        case 3:
            app->render->DrawTexture(inventoryPanel, 503, 258, &app->guiManager->rect4, false);
            break;
        case 4:
            app->render->DrawTexture(inventoryPanel, 432, 203, &app->guiManager->rect5, false);
            break;
        case 5:
            app->render->DrawTexture(inventoryPanel, 282, 155, &app->guiManager->rect6, false);
            break;
        case 6:
            app->render->DrawTexture(inventoryPanel, 227, 129, &app->guiManager->rect7, false);
            break;
        case 7:
            app->render->DrawTexture(inventoryPanel, 124, 104, &app->guiManager->rect8, false);
            break;
        case 8:
            app->render->DrawTexture(inventoryPanel, 61, 57, &app->guiManager->rect9, false);
            break;
        case 9:
            app->render->DrawTexture(inventoryPanel, 0, 0, NULL, false);
            break;
        }
    }
    else
    {
        switch (app->guiManager->anim)
        {
        case 0:
            app->render->DrawTexture(inventoryPanel, 603, 352, &app->guiManager->rect1, false);
            break;
        case 1:
            app->render->DrawTexture(inventoryPanel, 587, 326, &app->guiManager->rect2, false);
            break;
        case 2:
            app->render->DrawTexture(inventoryPanel, 560, 307, &app->guiManager->rect3, false);
            break;
        case 3:
            app->render->DrawTexture(inventoryPanel, 503, 258, &app->guiManager->rect4, false);
            break;
        case 4:
            app->render->DrawTexture(inventoryPanel, 432, 203, &app->guiManager->rect5, false);
            break;
        case 5:
            app->render->DrawTexture(inventoryPanel, 282, 155, &app->guiManager->rect6, false);
            break;
        case 6:
            app->render->DrawTexture(inventoryPanel, 227, 129, &app->guiManager->rect7, false);
            break;
        case 7:
            app->render->DrawTexture(inventoryPanel, 124, 104, &app->guiManager->rect8, false);
            break;
        case 8:
            app->render->DrawTexture(inventoryPanel, 61, 57, &app->guiManager->rect9, false);
            break;
        case 9:
            app->render->DrawTexture(inventoryPanel, 0, 0, NULL, false);
            break;
        }
    }

    std::vector<Item::EItemType>* inventory = app->inventory->GetInventory();
    size_t size = inventory->size();

    SDL_Rect itemrect = {
        0, 0,
        35, 35
    };

    iPoint ipos = { 105, 160 };

    size_t spacing = 29;

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
    if (control->id == partyBtn->id)
    {
        app->guiManager->cursor = 1;
    }
    else if (control->id == questBtn->id)
    {
        app->guiManager->cursor = 0;
    }

    return true;
}
