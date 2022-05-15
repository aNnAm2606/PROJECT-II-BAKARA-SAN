#include "VictoryPanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "TitleScreen.h"

VictoryPanel::VictoryPanel(bool active) : GuiPanel(active)
{
    Active = active;
}

VictoryPanel::~VictoryPanel()
{
}

bool VictoryPanel::Start()
{

    return true;
}

bool VictoryPanel::Update(float dt, bool doLogic)
{
    GuiPanel::Update(dt, doLogic);
    return true;
}

bool VictoryPanel::Draw()
{
    app->render->DrawTexture(app->guiManager->victoryScreen, -app->render->camera.x, -app->render->camera.y, NULL, true);
    GuiPanel::Draw();
    return true;
}

bool VictoryPanel::CleanUp()
{
    app->guiManager->victoryPanel->Disable();
    return true;
}

bool VictoryPanel::OnGuiMouseClickEvent(GuiControl* control)
{

    return true;
}
