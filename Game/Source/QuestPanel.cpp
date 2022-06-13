#include "QuestPanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "TitleScreen.h"
#include "Textures.h"

QuestPanel::QuestPanel(bool active) : GuiPanel(active)
{
    Active = active;
}

QuestPanel::~QuestPanel()
{
}

bool QuestPanel::Start()
{
    questPanel = app->tex->Load("Assets/Art/GUI/questUI.png");
    inventoryBtn = (GuiButton*)CreateGuiButton(0, app->guiManager, this, { 838,58,165,58 }, "inventory");
    inventoryBtn->texture = app->guiManager->titleButtons;
    inventoryBtn->normalRec = { 838,58,165,58 };
    inventoryBtn->focusedRec = { 838,58,165,58 };
    inventoryBtn->pressedRec = { 838,58,165,58 };

    partyBtn = (GuiButton*)CreateGuiButton(1, app->guiManager, this, { 1001,58,126,58 }, "party");
    partyBtn->texture = app->guiManager->titleButtons;
    partyBtn->normalRec = { 1001,58,126,58 };
    partyBtn->focusedRec = { 1001,58,126,58 };
    partyBtn->pressedRec = { 1001,58,126,58 };

    return true;
}

bool QuestPanel::Update(float dt, bool doLogic)
{
    GuiPanel::Update(dt, doLogic);
    return true;
}

bool QuestPanel::Draw()
{
    if (app->guiManager->cursorMode == true)
    {
        switch (app->guiManager->anim)
        {
        case 0:
            app->render->DrawTexture(questPanel, 603, 352, &app->guiManager->rect1, false);
            break;
        case 1:
            app->render->DrawTexture(questPanel, 587, 326, &app->guiManager->rect2, false);
            break;
        case 2:
            app->render->DrawTexture(questPanel, 560, 307, &app->guiManager->rect3, false);
            break;
        case 3:
            app->render->DrawTexture(questPanel, 503, 258, &app->guiManager->rect4, false);
            break;
        case 4:
            app->render->DrawTexture(questPanel, 432, 203, &app->guiManager->rect5, false);
            break;
        case 5:
            app->render->DrawTexture(questPanel, 282, 155, &app->guiManager->rect6, false);
            break;
        case 6:
            app->render->DrawTexture(questPanel, 227, 129, &app->guiManager->rect7, false);
            break;
        case 7:
            app->render->DrawTexture(questPanel, 124, 104, &app->guiManager->rect8, false);
            break;
        case 8:
            app->render->DrawTexture(questPanel, 61, 57, &app->guiManager->rect9, false);
            break;
        case 9:
            app->render->DrawTexture(questPanel, 0, 0, NULL, false);
            break;
        }
    }
    else
    {
        switch (app->guiManager->anim)
        {
        case 0:
            app->render->DrawTexture(questPanel, 603, 352, &app->guiManager->rect1, false);
            break;
        case 1:
            app->render->DrawTexture(questPanel, 587, 326, &app->guiManager->rect2, false);
            break;
        case 2:
            app->render->DrawTexture(questPanel, 560, 307, &app->guiManager->rect3, false);
            break;
        case 3:
            app->render->DrawTexture(questPanel, 503, 258, &app->guiManager->rect4, false);
            break;
        case 4:
            app->render->DrawTexture(questPanel, 432, 203, &app->guiManager->rect5, false);
            break;
        case 5:
            app->render->DrawTexture(questPanel, 282, 155, &app->guiManager->rect6, false);
            break;
        case 6:
            app->render->DrawTexture(questPanel, 227, 129, &app->guiManager->rect7, false);
            break;
        case 7:
            app->render->DrawTexture(questPanel, 124, 104, &app->guiManager->rect8, false);
            break;
        case 8:
            app->render->DrawTexture(questPanel, 61, 57, &app->guiManager->rect9, false);
            break;
        case 9:
            app->render->DrawTexture(questPanel, 0, 0, NULL, false);
            break;
        }
    }
    GuiPanel::Draw();
    return true;
}

bool QuestPanel::CleanUp()
{
    app->guiManager->questPanel->Disable();
    return true;
}

bool QuestPanel::OnGuiMouseClickEvent(GuiControl* control)
{
    if (control->id == inventoryBtn->id)
    {
        app->guiManager->cursor = 0;
    } 
    else if (control->id == partyBtn->id)
    {
        app->guiManager->cursor = 1;
    }
    return true;
}
