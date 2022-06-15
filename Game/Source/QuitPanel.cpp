#include "QuitPanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "TitleScreen.h"

QuitPanel::QuitPanel(bool active) : GuiPanel(active)
{
    Active = active;
}

QuitPanel::~QuitPanel()
{
}

bool QuitPanel::Start()
{
    box = {0,0,744,297};

    closeGame = false;

    yesBtn = (GuiButton*)CreateGuiButton(0, app->guiManager, this, { app->render->camera.x + 280+268,app->render->camera.y + 180+212,55,30}, "Quit Game");
    yesBtn->texture = app->guiManager->quitBox;
    yesBtn->normalRec = { 20,325,55,30 };
    yesBtn->focusedRec = { 155,325,55,30 };
    yesBtn->pressedRec = { 288,325,55,30 };

    noBtn = (GuiButton*)CreateGuiButton(1, app->guiManager, this, { app->render->camera.x + 420+268,app->render->camera.y + 180+212,41,30 }, "Continue Game");
    noBtn->texture = app->guiManager->quitBox;
    noBtn->normalRec = { 80,325,41,30 };
    noBtn->focusedRec = { 215,325,41,30 };
    noBtn->pressedRec = { 348,325,41,30 };

    return true;
}

bool QuitPanel::Update(float dt, bool doLogic)
{
    GuiPanel::Update(dt, doLogic);
    return true;
}

bool QuitPanel::Draw()
{
    app->render->DrawTexture(app->guiManager->quitBox, 268,  212, &box, false);
    GuiPanel::Draw();
    return true;
}

bool QuitPanel::CleanUp()
{
    app->guiManager->quitPanel->Disable();
    return true;
}

bool QuitPanel::OnGuiMouseClickEvent(GuiControl* control)
{
    if(control->id == noBtn->id)
    {
        app->guiManager->quitPanel->Disable();
    }
    else if (control->id == yesBtn->id)
    {
        closeGame = true;
    }

    return true;
}
