#include "Credits.h"
#include "Log.h"
#include "App.h"
#include "Audio.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "TitleScreen.h"
#include "Transitions.h"

Credits::Credits(bool active) : GuiPanel(active)
{
    Active = active;
}

Credits::~Credits()
{
}

bool Credits::Start()
{
    closeBtn = (GuiButton*)CreateGuiButton(0, app->guiManager, this, { 1230,25,23,26}, "close credits");
    closeBtn->texture = app->guiManager->credits;

    return true;
}

bool Credits::Update(float dt, bool doLogic)
{
    GuiPanel::Update(dt, doLogic);

    if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
        app->guiManager->creditsPanel->Disable();
        app->audio->ChangeMusic(TITLE_MUSIC, 0.0f, 0.0f);
    }

    return true;
}

bool Credits::Draw()
{
    app->render->DrawTextureScaled(app->guiManager->credits, 0, 0, 1280, 720, NULL);
    GuiPanel::Draw();
    return true;
}

bool Credits::CleanUp()
{
    app->guiManager->creditsPanel->Disable();
    return true;
}

bool Credits::OnGuiMouseClickEvent(GuiControl* control)
{
    /*if(control->id == closeBtn->id)
    {
        app->guiManager->creditsPanel->Disable();
        app->audio->ChangeMusic(TITLE_MUSIC, 0.0f, 0.0f);
    }*/

    return true;
}
