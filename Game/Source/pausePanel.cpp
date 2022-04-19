#include "pausePanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "TitleScreen.h"

pausePanel::pausePanel(bool active) : GuiPanel(active)
{
    Active = active;
}

pausePanel::~pausePanel()
{
}

bool pausePanel::Start()
{
    closeBtn = (GuiButton*)CreateGuiButton(0, app->guiManager, this, { 1230,25,23,26}, "close credits");
    closeBtn->texture = app->guiManager->credits;

    return true;
}

bool pausePanel::Update(float dt, bool doLogic)
{
    GuiPanel::Update(dt, doLogic);
    return true;
}

bool pausePanel::Draw()
{
    app->render->DrawTexture(app->guiManager->credits, 0, 0, NULL);
    GuiPanel::Draw();
    return true;
}

bool pausePanel::CleanUp()
{
    app->guiManager->creditsPanel->Disable();
    return true;
}

bool pausePanel::OnGuiMouseClickEvent(GuiControl* control)
{
    if(control->id == closeBtn->id)
    {
        app->guiManager->creditsPanel->Disable();
    }

    return true;
}
