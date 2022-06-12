#include "PartyPanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "TitleScreen.h"
#include "Textures.h"
#include "Input.h"

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
    paladinStats = app->tex->Load("Assets/Art/GUI/paladinStats.png");
    paladinPic = app->tex->Load("Assets/Art/GUI/paladinPicture.png");
    monkStats = app->tex->Load("Assets/Art/GUI/monkStats.png");
    monkPic = app->tex->Load("Assets/Art/GUI/monkPicture.png");
    priestStats = app->tex->Load("Assets/Art/GUI/priestStats.png");
    priestPic = app->tex->Load("Assets/Art/GUI/priestPicture.png");

    return true;
}

bool PartyPanel::Update(float dt, bool doLogic)
{
    GuiPanel::Update(dt, doLogic);
    if (app->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::KEY_DOWN) selected = selected + 1;
    if (selected > 3) selected = 0;
    return true;
}

bool PartyPanel::Draw()
{
    app->render->DrawTexture(app->guiManager->partyScreen, -app->render->camera.x, -app->render->camera.y, NULL, true);
    app->render->DrawTexture(chamanPic,  101, 155, NULL, false);
    app->render->DrawTexture(paladinPic, 217, 155, NULL, false);
    app->render->DrawTexture(monkPic, 337,155, NULL, false);
    app->render->DrawTexture(priestPic, 458, 155, NULL, false);

    switch (selected)
    {
    case 0:
        app->render->DrawTexture(chamanStats, 579, 142, NULL, false);
        break;
    case 1:
        app->render->DrawTexture(paladinStats, 579, 142, NULL, false);
        break;
    case 2:
        app->render->DrawTexture(monkStats, 579, 142, NULL, false);
        break;
    case 3:
        app->render->DrawTexture(priestStats, 579, 142, NULL, false);
        break;
    }

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
