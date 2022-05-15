#include "PartyPanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "TitleScreen.h"
#include "Textures.h"

PartyPanel::PartyPanel(bool active) : GuiPanel(active)
{
    Active = active;
}

PartyPanel::~PartyPanel()
{
}

bool PartyPanel::Start()
{
    chamanStats = app->tex->Load("Assets/Art/GUI/chamanStats.png");
    chamanPic = app->tex->Load("Assets/Art/GUI/chamanPicture.png");
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
    app->render->DrawTexture(chamanStats, -app->render->camera.x + 579, -app->render->camera.y + 142, NULL, true);
    app->render->DrawTexture(chamanPic, -app->render->camera.x + 101, -app->render->camera.y + 155, NULL, true);
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
