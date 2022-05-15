#include "InventoryPanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "TitleScreen.h"

InventoryPanel::InventoryPanel(bool active) : GuiPanel(active)
{
    Active = active;
}

InventoryPanel::~InventoryPanel()
{
}

bool InventoryPanel::Start()
{

    return true;
}

bool InventoryPanel::Update(float dt, bool doLogic)
{
    GuiPanel::Update(dt, doLogic);
    return true;
}

bool InventoryPanel::Draw()
{
    app->render->DrawTexture(app->guiManager->inventoryScreen, -app->render->camera.x, -app->render->camera.y, NULL, true);
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
