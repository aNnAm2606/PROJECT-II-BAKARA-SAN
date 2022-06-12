#include "SettingsPanel.h"
#include "Log.h"
#include "App.h"
#include "Audio.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "PausePanel.h"
#include "Window.h"
#include "Transitions.h"

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
    fullscreen = app->win->fullscreen;

    volumeSldr = (GuiSlider*)CreateGuiSlider(0, app->guiManager, this, { 350 + 76,133 + 73, 620 ,30 }, { 355, 130, 36 * 2 ,36 });
    volumeSldr->texture = app->guiManager->settingsBox;
    volumeSldr->thumbRect = { 205,582,36,36 };
    volumeSldr->SetValue(128);

    musicSldr = (GuiSlider*)CreateGuiSlider(1, app->guiManager, this, { 350 + 76,173 + 73, 620 ,30 }, { 355, 130, 36 * 2 ,36 });
    musicSldr->texture = app->guiManager->settingsBox;
    musicSldr->thumbRect = { 205,582,36,36 };
    musicSldr->SetValue(128);

    fxSldr = (GuiSlider*)CreateGuiSlider(2, app->guiManager, this, { 350 + 76,210 + 73, 620 ,30 }, { 355, 130, 36 * 2 ,36 });
    fxSldr->texture = app->guiManager->settingsBox;
    fxSldr->thumbRect = { 205,582,36,36 };
    fxSldr->SetValue(128);

    fullSrnON = (GuiToggle*)CreateGuiCheckBox(3, app->guiManager, this, { 350 + 76,285 + 73,50,30 });
    fullSrnON->texture = app->guiManager->settingsBox;
    fullSrnON->normalRec = { 350,285,50,30 };
    fullSrnON->selectedRec = { 5,580, 50,30 };

    fullSrnOff = (GuiToggle*)CreateGuiCheckBox(4, app->guiManager, this, { 420+76, 285+73, 45, 35 });
    fullSrnOff->texture = app->guiManager->settingsBox;
    fullSrnOff->normalRec = { 420,285,45,35 };
    fullSrnOff->selectedRec = { 75,580,45,35};
    fullSrnOff->State = true;

    vsyncOn = (GuiToggle*)CreateGuiCheckBox(6, app->guiManager, this, { 350 + 76,327 + 73,50,30 });
    vsyncOn->texture = app->guiManager->settingsBox;
    vsyncOn->normalRec = { 350,285,50,30 };
    vsyncOn->selectedRec = { 5,580, 50,30 };
    vsyncOn->State = true;

    vsyncOff = (GuiToggle*)CreateGuiCheckBox(7, app->guiManager, this, { 420 + 76, 327 + 73, 45, 35 });
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
    app->audio->SetMusicVolume(MUSIC_VOLUME * (musicSldr->value/128));

    if (fullscreen == false)
    {
        fullSrnOff->state = GuiControlState::SELECTED;
        fullSrnON->state = GuiControlState::NORMAL;
    }
    else
    {
        fullSrnOff->state = GuiControlState::NORMAL;
        fullSrnON->state = GuiControlState::SELECTED;
    }

    return true;
}

bool SettingsPanel::Draw()
{
    app->transitions->UiAnim(5, -500, 100);
    app->render->DrawTexture(app->guiManager->settingsBox, 76, 73, &box ,false);
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

    if(control->id == fullSrnON->id)
    {
        fullscreen = fullSrnON->State;
        app->win->SetFullScreen(fullscreen);
        app->render->SetFullScreen();
    }
    else if (control->id == fullSrnOff->id)
    {
        fullscreen = !fullSrnOff->State;
        app->win->SetFullScreen(fullscreen);
        app->render->SetFullScreen();
    }

    if (control->id == vsyncOn->id)
    {
        app->render->vsync = true;
        app->render->SetVsync(app->render->vsync);
    }
    else if (control->id == vsyncOff->id)
    {
    }
    
    if (control->id ==musicSldr->id)
    { 
        app->audio->SetMusicVolume(musicSldr->GetValue());
        LOG("VOLUME %i", app->audio->GetMusicVolume());
        LOG("sldr value %i", musicSldr->GetValue());
    }

    else if (control->id == fxSldr->id)
    {
        app->audio->SetSFXVolume(fxSldr->GetValue());
        LOG("FX VOLUME %i", app->audio->GetFxVolume());
        LOG("RX sldr value %i", fxSldr->GetValue());
    }

    return true;
}
