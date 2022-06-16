#include "LosePanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "TitleScreen.h"
#include "Textures.h"
#include "Transitions.h"
#include "Input.h"
#include "Audio.h"

LosePanel::LosePanel(bool active) : GuiPanel(active)
{
    Active = active;
}

LosePanel::~LosePanel()
{
}

bool LosePanel::Start()
{
    return true;
}

bool LosePanel::Update(float dt, bool doLogic)
{
    GamePad& gamepad = app->input->pads[0];

    if (app->input->GamepadConnected() == false)
    {
        if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) CleanUp();
    }
    else if (gamepad.a == true) CleanUp();
    GuiPanel::Update(dt, doLogic);
    return true;
}

bool LosePanel::Draw()
{
    app->render->DrawTexture(app->guiManager->loseScreen, -app->render->camera.x, -app->render->camera.y, NULL, true);
    GuiPanel::Draw();
    return true;
}

bool LosePanel::CleanUp()
{
    app->guiManager->losePanel->Disable();
    return true;
}

bool LosePanel::OnGuiMouseClickEvent(GuiControl* control)
{

    return true;
}
