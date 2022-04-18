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

    continueBtn = (GuiButton*)CreateGuiButton(1, app->guiManager, this, { 950, 460, 170,60 }, "Continue Game");
    continueBtn->texture = app->guiManager->titleButtons;
    continueBtn->normalRec = { 130,15,126,32 };
    continueBtn->focusedRec = { 130,50,126,32 };
    continueBtn->pressedRec = { 130,15,126,32 };


    //settingsBtn = (GuiButton*)CreateGuiButton(2, app->guiManager, this, { this->position.x + 555, this->position.y + 370, 170,60 }, "Settings");
    //settingsBtn->texture = app->guiManager->settingsBox;
    //settingsBtn->normalRec = { 0,0,170,60 };
    //settingsBtn->focusedRec = { 0,120,170,60 };
    //settingsBtn->pressedRec = { 0,59,170,60 };

    //quitBtn = (GuiButton*)CreateGuiButton(3, app->guiManager, this, { this->position.x + 555, this->position.y + 460, 170,60 }, "Quit Game");
    //quitBtn->texture = app->guiManager->exitBox;
    //quitBtn->normalRec = { 0,0,170,60 };
    //quitBtn->focusedRec = { 0,120,170,60 };
    //quitBtn->pressedRec = { 0,59,170,60 };

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
       /* app->levelManagement->gameState = GameState::THE_FALL;*/
      /*  app->fade->Fade((Module*)app->titleScreen, (Module*)app->logoScreen);*/
        app->titleScreen->startGame = true;
    }
    //else if (control->id == bt_loadGame->id)
    //{
    //    //load Game
    //}
    //else if (control->id == bt_settings->id)
    //{
    //    app->guiManager->pn_settings->Enable();
    //    app->guiManager->pn_start->Disable();
    //}
    //else if (control->id == bt_quit->id)
    //{
    //    //close game

    //}

    return true;
}
