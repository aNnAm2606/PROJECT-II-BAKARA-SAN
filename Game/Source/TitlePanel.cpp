#include "TitlePanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "TitleScreen.h"

TitlePanel::TitlePanel(bool active) : GuiPanel(active)
{
    Active = active;
}

TitlePanel::~TitlePanel()
{

}

bool TitlePanel::Start()
{
    startBtn = (GuiButton*)CreateGuiButton(0, app->guiManager, this, { 950 ,400,81,31 }, "Start New Game");
    startBtn->texture = app->guiManager->titleButtons;
    startBtn->normalRec = { 15,15,81,31 };
    startBtn->focusedRec = { 15,50,81,31 };
    startBtn->pressedRec = { 15,15,81,31 };

    continueBtn = (GuiButton*)CreateGuiButton(1, app->guiManager, this, { 950, 450, 126, 31 }, "Continue Game");
    continueBtn->texture = app->guiManager->titleButtons;
    continueBtn->normalRec = { 130,15,126,32 };
    continueBtn->focusedRec = { 130,50,126,32 };
    continueBtn->pressedRec = { 130,15,126,32 };

    settingsBtn = (GuiButton*)CreateGuiButton(2, app->guiManager, this, { 950, 500, 120, 34 }, "Settings");
    settingsBtn->texture = app->guiManager->titleButtons;
    settingsBtn->normalRec = { 285,17,120,34 };
    settingsBtn->focusedRec = { 285,50,120,34 };
    settingsBtn->pressedRec = { 285,17,120,34 };

    creditsBtn = (GuiButton*)CreateGuiButton(3, app->guiManager, this, { 950, 550, 106, 28 }, "Credits");
    creditsBtn->texture = app->guiManager->titleButtons;
    creditsBtn->normalRec = { 521,21,106,28 };
    creditsBtn->focusedRec = { 521,52,106,28 };
    creditsBtn->pressedRec = { 521,21,106,28 };

    quitBtn = (GuiButton*)CreateGuiButton(4, app->guiManager, this, { 950, 600, 66, 32 }, "Quit Game");
    quitBtn->texture = app->guiManager->titleButtons;
    quitBtn->normalRec = { 432,19,66,32 };
    quitBtn->focusedRec = { 432,52,66,32 };
    quitBtn->pressedRec = { 432,19,66,32 };

    return true;
}

bool TitlePanel::Update(float dt, bool doLogic)
{
    GuiPanel::Update(dt, doLogic);
    return true;
}

bool TitlePanel::Draw()
{
    GuiPanel::Draw();
    return true;
}

bool TitlePanel::CleanUp()
{
    app->guiManager->titlePanel->Disable();
    return true;
}

bool TitlePanel::OnGuiMouseClickEvent(GuiControl* control)
{
    if(control->id == startBtn->id)
    {
        app->titleScreen->startGame = true;
    }
    else if (control->id == continueBtn->id)
    {
        /*app->guiManager->pausePanel->Enable();
        app->guiManager->titlePanel->Disable();
        app->guiManager->pausePanel->gamePaused = true;*/
        //app->LoadGameRequest();
        app->titleScreen->startGame = true;
        app->titleScreen->continueGame = true;
    }
    else if (control->id == settingsBtn->id)
    {
        app->guiManager->settingsPanel->Enable();
        app->guiManager->titlePanel->Disable();
    }
    else if (control->id == quitBtn->id)
    {
        app->guiManager->quitPanel->Enable();
        app->guiManager->titlePanel->Disable();
    }
    else if (control->id == creditsBtn->id)
    {
        app->guiManager->creditsPanel->Enable();
        app->guiManager->titlePanel->Disable();
    }

    return true;
}
