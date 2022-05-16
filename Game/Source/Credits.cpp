#include "Credits.h"
#include "Log.h"
#include "App.h"
#include "Audio.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "TitleScreen.h"

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
    return true;
}

bool Credits::Draw()
{
    app->render->DrawTexture(app->guiManager->credits, 0, 0, NULL);
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
    if(control->id == closeBtn->id)
    {
        app->guiManager->creditsPanel->Disable();
        app->audio->ChangeMusic(TITLE_MUSIC, 0.0f, 0.0f);
    }

    return true;
}
