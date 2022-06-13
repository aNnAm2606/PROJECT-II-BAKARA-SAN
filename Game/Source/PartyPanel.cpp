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
    partyPanel = app->tex->Load("Assets/Art/GUI/partyUI.png");

    inventoryBtn = (GuiButton*)CreateGuiButton(0, app->guiManager, this, { 838,58,165,58 }, "inventory");
    inventoryBtn->texture = app->guiManager->titleButtons;
    inventoryBtn->normalRec = { 838,58,165,58 };
    inventoryBtn->focusedRec = { 838,58,165,58 };
    inventoryBtn->pressedRec = { 838,58,165,58 };

    questBtn = (GuiButton*)CreateGuiButton(1, app->guiManager, this, { 1128,58,124,58 }, "quest");
    questBtn->texture = app->guiManager->titleButtons;
    questBtn->normalRec = { 1128,58,124,58 };
    questBtn->focusedRec = { 1128,58,124,58 };
    questBtn->pressedRec = { 1128,58,124,58 };

    Btn1 = (GuiButton*)CreateGuiButton(2, app->guiManager, this, { 100,155,100,100 }, "char 1");
    Btn1->texture = app->guiManager->titleButtons;
    Btn1->normalRec = { 100,155,100,100 };
    Btn1->focusedRec = { 100,155,100,100 };
    Btn1->pressedRec = { 100,155,100,100 };

    Btn2 = (GuiButton*)CreateGuiButton(3, app->guiManager, this, { 216,155,100,100 }, "char 2");
    Btn2->texture = app->guiManager->titleButtons;
    Btn2->normalRec = { 100,155,100,100 };
    Btn2->focusedRec = { 100,155,100,100 };
    Btn2->pressedRec = { 100,155,100,100 };

    Btn3 = (GuiButton*)CreateGuiButton(4, app->guiManager, this, { 336,155,100,100 }, "char 3");
    Btn3->texture = app->guiManager->titleButtons;
    Btn3->normalRec = { 100,155,100,100 };
    Btn3->focusedRec = { 100,155,100,100 };
    Btn3->pressedRec = { 100,155,100,100 };

    Btn4 = (GuiButton*)CreateGuiButton(5, app->guiManager, this, { 457,155,100,100 }, "char 4");
    Btn4->texture = app->guiManager->titleButtons;
    Btn4->normalRec = { 100,155,100,100 };
    Btn4->focusedRec = { 100,155,100,100 };
    Btn4->pressedRec = { 100,155,100,100 };

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
    if (app->guiManager->cursorMode == true)
    {
        switch (app->guiManager->anim)
        {
        case 0:
            app->render->DrawTexture(partyPanel, 603, 352, &app->guiManager->rect1, false);
            break;
        case 1:
            app->render->DrawTexture(partyPanel, 587, 326, &app->guiManager->rect2, false);
            break;
        case 2:
            app->render->DrawTexture(partyPanel, 560, 307, &app->guiManager->rect3, false);
            break;
        case 3:
            app->render->DrawTexture(partyPanel, 503, 258, &app->guiManager->rect4, false);
            break;
        case 4:
            app->render->DrawTexture(partyPanel, 432, 203, &app->guiManager->rect5, false);
            break;
        case 5:
            app->render->DrawTexture(partyPanel, 282, 155, &app->guiManager->rect6, false);
            break;
        case 6:
            app->render->DrawTexture(partyPanel, 227, 129, &app->guiManager->rect7, false);
            break;
        case 7:
            app->render->DrawTexture(partyPanel, 124, 104, &app->guiManager->rect8, false);
            break;
        case 8:
            app->render->DrawTexture(partyPanel, 61, 57, &app->guiManager->rect9, false);
            break;
        case 9:
            app->render->DrawTexture(partyPanel, 0, 0, NULL, false);
            app->render->DrawTexture(chamanPic, 101, 155, NULL, false);
            app->render->DrawTexture(paladinPic, 217, 155, NULL, false);
            app->render->DrawTexture(monkPic, 337, 155, NULL, false);
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
            break;
        }
        
    }
    else
    {
        switch (app->guiManager->anim)
        {
        case 0:
            app->render->DrawTexture(partyPanel, 603, 352, &app->guiManager->rect1, false);
            break;
        case 1:
            app->render->DrawTexture(partyPanel, 587, 326, &app->guiManager->rect2, false);
            break;
        case 2:
            app->render->DrawTexture(partyPanel, 560, 307, &app->guiManager->rect3, false);
            break;
        case 3:
            app->render->DrawTexture(partyPanel, 503, 258, &app->guiManager->rect4, false);
            break;
        case 4:
            app->render->DrawTexture(partyPanel, 432, 203, &app->guiManager->rect5, false);
            break;
        case 5:
            app->render->DrawTexture(partyPanel, 282, 155, &app->guiManager->rect6, false);
            break;
        case 6:
            app->render->DrawTexture(partyPanel, 227, 129, &app->guiManager->rect7, false);
            break;
        case 7:
            app->render->DrawTexture(partyPanel, 124, 104, &app->guiManager->rect8, false);
            break;
        case 8:
            app->render->DrawTexture(partyPanel, 61, 57, &app->guiManager->rect9, false);
            break;
        case 9:
            app->render->DrawTexture(partyPanel, 0, 0, NULL, false);
            break;
        }

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
    if (control->id == inventoryBtn->id)
    {
        app->guiManager->cursor = 0;
    }
    else if (control->id == questBtn->id)
    {
        app->guiManager->cursor = 2;
    }

    if (control->id == Btn1->id)
    {
        selected = 0;
    }
    else if (control->id == Btn2->id)
    {
        selected = 1;
    }
    else if (control->id == Btn3->id)
    {
        selected = 2;
    }
    else if (control->id == Btn4->id)
    {
        selected = 3;
    }

    return true;
}
