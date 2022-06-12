#include "PausePanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "TitleScreen.h"
#include "Transitions.h"

PausePanel::PausePanel(bool active) : GuiPanel(active)
{
    Active = active;
}

PausePanel::~PausePanel()
{
}

bool PausePanel::Start()
{
    box = {254,0,407,544};

    resumeBtn = (GuiButton*)CreateGuiButton(0, app->guiManager, this, { 574,131+88,131,32}, "resume Game");
    resumeBtn->texture = app->guiManager->pauseBox;
    resumeBtn->normalRec = { 395,131,131,32 };
    resumeBtn->focusedRec = { 53,131,131,32 };
    resumeBtn->pressedRec = { 725,131,131,32 };

    settingsBtn = (GuiButton*)CreateGuiButton(1, app->guiManager, this, { 568,192+88,143,43 }, "settings panel");
    settingsBtn->texture = app->guiManager->pauseBox;
    settingsBtn->normalRec = { 386,192,143,43 };
    settingsBtn->focusedRec = { 47,192,143,43 };
    settingsBtn->pressedRec = { 717,192,143,43 };

    saveBtn = (GuiButton*)CreateGuiButton(2, app->guiManager, this, { 590,254+88,84,34 }, "save Game");
    saveBtn->texture = app->guiManager->pauseBox;
    saveBtn->normalRec = { 409,254,84,34 };
    saveBtn->focusedRec = { 68,254,84,34 };
    saveBtn->pressedRec = { 740,254,84,34 };

    loadBtn = (GuiButton*)CreateGuiButton(3, app->guiManager, this, { 592,313+88,93,33 }, "load Game");
    loadBtn->texture = app->guiManager->pauseBox;
    loadBtn->normalRec = { 408,313,93,33 };
    loadBtn->focusedRec = { 67,313,93,33 };
    loadBtn->pressedRec = { 740,313,93,33 };

    exitGameBtn = (GuiButton*)CreateGuiButton(4, app->guiManager, this, { 551,377+88,177,43 }, "exit Game");
    exitGameBtn->texture = app->guiManager->pauseBox;
    exitGameBtn->normalRec = { 368,377,177,43 };
    exitGameBtn->focusedRec = { 27,377,177,43 };
    exitGameBtn->pressedRec = { 698,377,177,43 };

    return true;
}

bool PausePanel::Update(float dt, bool doLogic)
{
    GuiPanel::Update(dt, doLogic);

    return true;
}

bool PausePanel::Draw()
{
    app->transitions->UiAnim(6, -500, 150);
    app->render->DrawTexture(app->guiManager->pauseBox, 436, 88, &box, false);
    GuiPanel::Draw();
    return true;
}

bool PausePanel::CleanUp()
{
    app->guiManager->pausePanel->Disable();
    gamePaused = false;
    return true;
}

bool PausePanel::OnGuiMouseClickEvent(GuiControl* control)
{
    if(control->id == resumeBtn->id)
    {
        app->guiManager->pausePanel->Disable();
        gamePaused = false;
    }
    else if (control->id == settingsBtn->id)
    {
        app->guiManager->settingsPanel->Enable();
        app->guiManager->pausePanel->Disable();
    }
    else if (control->id == saveBtn->id)
    {
        app->SaveGameRequest();
        app->guiManager->pausePanel->Disable();
    }
    else if (control->id == loadBtn->id)
    {
        app->LoadGameRequest();
        app->guiManager->pausePanel->Disable();

    }
    else if (control->id == exitGameBtn->id)
    {
        app->guiManager->quitPanel->Enable();
        app->guiManager->pausePanel->Disable();
        gamePaused = false;
    }

    return true;
}
