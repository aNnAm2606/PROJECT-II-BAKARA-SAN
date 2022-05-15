#include "PartyPanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "TitleScreen.h"

PartyPanel::PartyPanel(bool active) : GuiPanel(active)
{
    Active = active;
}

PartyPanel::~PartyPanel()
{
}

bool PartyPanel::Start()
{

    return true;
}

bool PartyPanel::Update(float dt, bool doLogic)
{
    GuiPanel::Update(dt, doLogic);
    return true;
}

bool PartyPanel::Draw()
{
    app->render->DrawTexture(app->guiManager->partyScreen, -app->render->camera.x, -app->render->camera.y, NULL, true);
    GuiPanel::Draw();
    return true;
}

bool PartyPanel::CleanUp()
{
    app->guiManager->partyPanel->Disable();
    return true;
}

bool PartyPanel::OnGuiMouseClickEvent(GuiControl* control)
{

    return true;
}
