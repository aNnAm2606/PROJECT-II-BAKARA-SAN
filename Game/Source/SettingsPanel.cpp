#include "SettingsPanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "PausePanel.h"

SettingsPanel::SettingsPanel(bool active) : GuiPanel(active)
{
    Active = active;
}

SettingsPanel::~SettingsPanel()
{

}

bool SettingsPanel::Start()
{
    box = { 0,0,1129,580 };

    volumeSldr = (GuiSlider*)CreateGuiSlider(0, app->guiManager, this, { 350 + 76,133 + 73, 620 ,30 }, { 355, 130, 36 * 2 ,36 });
    volumeSldr->texture = app->guiManager->settingsBox;
    volumeSldr->thumbRect = { 205,582,36,36 };

    musicSldr = (GuiSlider*)CreateGuiSlider(1, app->guiManager, this, { 350 + 76,173 + 73, 620 ,30 }, { 355, 130, 36 * 2 ,36 });
    musicSldr->texture = app->guiManager->settingsBox;
    musicSldr->thumbRect = { 205,582,36,36 };

    fxSlrd = (GuiSlider*)CreateGuiSlider(2, app->guiManager, this, { 350 + 76,210 + 73, 620 ,30 }, { 355, 130, 36 * 2 ,36 });
    fxSlrd->texture = app->guiManager->settingsBox;
    fxSlrd->thumbRect = { 205,582,36,36 };

    fullSrnON = (GuiToggle*)CreateGuiCheckBox(3, app->guiManager, this, { 350 + 76,285 + 73,50,30 });
    fullSrnON->texture = app->guiManager->settingsBox;
    fullSrnON->normalRec = { 350,285,50,30 };
    fullSrnON->selectedRec = { 5,580, 50,30 };

    fullSrnOff = (GuiToggle*)CreateGuiCheckBox(4, app->guiManager, this, { 420+76, 285+73, 45, 35 });
    fullSrnOff->texture = app->guiManager->settingsBox;
    fullSrnOff->normalRec = { 420,285,45,35 };
    fullSrnOff->selectedRec = { 75,580,45,35};

    vsyncOn = (GuiToggle*)CreateGuiCheckBox(3, app->guiManager, this, { 350 + 76,285 + 73,50,30 });
    vsyncOn->texture = app->guiManager->settingsBox;
    vsyncOn->normalRec = { 350,285,50,30 };
    vsyncOn->selectedRec = { 5,580, 50,30 };

    vsyncOn = (GuiToggle*)CreateGuiCheckBox(4, app->guiManager, this, { 420 + 76, 285 + 73, 45, 35 });
    vsyncOn->texture = app->guiManager->settingsBox;
    vsyncOn->normalRec = { 420,285,45,35 };
    vsyncOn->selectedRec = { 75,580,45,35 };

    vsyncOff = (GuiToggle*)CreateGuiCheckBox(3, app->guiManager, this, { 350 + 76,327 + 73,50,30 });
    vsyncOff->texture = app->guiManager->settingsBox;
    vsyncOff->normalRec = { 350,285,50,30 };
    vsyncOff->selectedRec = { 5,580, 50,30 };

    vsyncOff = (GuiToggle*)CreateGuiCheckBox(4, app->guiManager, this, { 420 + 76, 327 + 73, 45, 35 });
    vsyncOff->texture = app->guiManager->settingsBox;
    vsyncOff->normalRec = { 420,285,45,35 };
    vsyncOff->selectedRec = { 75,580,45,35 };

    returnbtn = (GuiButton*)CreateGuiButton(5, app->guiManager, this, { 535 + 76, 480 + 73, 90, 25 }, "Close Settings");
    returnbtn->texture = app->guiManager->settingsBox;
    returnbtn->normalRec = { 535,480,90,25 };
    returnbtn->focusedRec = { 535,480,90,25 };
    returnbtn->pressedRec = { 535,480,90,25 };

    quitBtn = (GuiButton*)CreateGuiButton(5, app->guiManager, this, { 1050+76, 75+73, 25, 30 }, "Close Settings");
    quitBtn->texture = app->guiManager->settingsBox;
    quitBtn->normalRec = { 1050,75,25,30 };
    quitBtn->focusedRec = { 145,586,25,30 };
    quitBtn->pressedRec = { 1050,75,25,30 };

    return true;
}

bool SettingsPanel::Update(float dt, bool doLogic)
{
    GuiPanel::Update(dt, doLogic);
    return true;
}

bool SettingsPanel::Draw()
{
    app->render->DrawTexture(app->guiManager->settingsBox, -app->render->camera.x + 76, -app->render->camera.y + 73, &box);
    GuiPanel::Draw();
    return true;
}

bool SettingsPanel::CleanUp()
{
    app->guiManager->settingsPanel->Disable();
    return true;
}

bool SettingsPanel::OnGuiMouseClickEvent(GuiControl* control)
{
    if (app->guiManager->pausePanel->gamePaused == true && (control->id == quitBtn->id || control->id == returnbtn->id))
    {
        app->guiManager->settingsPanel->Disable();
        app->guiManager->pausePanel->Enable();
    }
    else if (app->guiManager->pausePanel->gamePaused == false && (control->id == quitBtn->id || control->id == returnbtn->id))
    {
        app->guiManager->settingsPanel->Disable();
    }
    else if(control->id == fullSrnON->id)
    {
        if (fullSrnON->State == true)
            fullSrnOff->State = false;
    }

    return true;
}
