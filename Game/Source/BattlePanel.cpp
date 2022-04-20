#include "BattlePanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "TitleScreen.h"

BattlePanel::BattlePanel(bool active) : GuiPanel(active)
{
    Active = active;
}

BattlePanel::~BattlePanel()
{
}

bool BattlePanel::Start()
{
    charBox = { 0, 0, 310, 210 };
    actionBox = { 554, 0, 148, 210 };
    enemyBox = { 330, 0, 210, 210 };
    arrow = { 410, 210, 16, 36 };

    // Character selection
    ChamanBtn = (GuiButton*)CreateGuiButton(0, app->guiManager, this, { app->render->camera.x + 150 + 35,app->render->camera.y + 460 + 25,90,25 }, "Chaman selected");
    ChamanBtn->texture = app->guiManager->battleBox;
    ChamanBtn->normalRec = { 515,355,90,25 };
    ChamanBtn->focusedRec = { 515,355,90,25 };
    ChamanBtn->pressedRec = { 515,355,90,25 };

    PaladinBtn = (GuiButton*)CreateGuiButton(1, app->guiManager, this, { app->render->camera.x + 150 + 35,app->render->camera.y + 460 + 100,90,25 }, "Chaman selected");
    PaladinBtn->texture = app->guiManager->battleBox;
    PaladinBtn->normalRec = { 610,355,90,25 };
    PaladinBtn->focusedRec = { 610,355,90,25 };
    PaladinBtn->pressedRec = { 610,355,90,25 };

    // Action select
    attackBtn = (GuiButton*)CreateGuiButton(2, app->guiManager, this, { app->render->camera.x + 480 + 35,app->render->camera.y + 460 + 25,70,25 }, "Attack selected");
    attackBtn->texture = app->guiManager->battleBox;
    attackBtn->normalRec = { 515,210,70,25 };
    attackBtn->focusedRec = { 515,235,70,25 };
    attackBtn->pressedRec = { 515,260,70,25 };

    dodgeBtn = (GuiButton*)CreateGuiButton(3, app->guiManager, this, { app->render->camera.x + 480 + 35,app->render->camera.y + 460 + 75,45,25 }, "Dodge selected");
    dodgeBtn->texture = app->guiManager->battleBox;
    dodgeBtn->normalRec = { 585,210,45,25 };
    dodgeBtn->focusedRec = { 585,235,45,25 };
    dodgeBtn->pressedRec = { 585,260,45,25 };

    runBtn = (GuiButton*)CreateGuiButton(4, app->guiManager, this, { app->render->camera.x + 480 + 35,app->render->camera.y + 460 + 125,64,29 }, "Run selected");
    runBtn->texture = app->guiManager->battleBox;
    runBtn->normalRec = { 635,210,64,28 };
    runBtn->focusedRec = { 635,237,64,27 };
    runBtn->pressedRec = { 635,262,64,27 };

    // Enemy selection
    fallenAngelBtn = (GuiButton*)CreateGuiButton(5, app->guiManager, this, { app->render->camera.x + 930 + 35,app->render->camera.y + 460 + 25,130,28 }, "Fallen Angel selected");
    fallenAngelBtn->texture = app->guiManager->battleBox;
    fallenAngelBtn->normalRec = { 395,295,130,28 };
    fallenAngelBtn->focusedRec = { 395,320,130,28 };
    fallenAngelBtn->pressedRec = { 395,295,130,28 };

    ghostBtn = (GuiButton*)CreateGuiButton(6, app->guiManager, this, { app->render->camera.x + 930 + 35,app->render->camera.y + 460 + 75,66,28 }, "Ghost selected");
    ghostBtn->texture = app->guiManager->battleBox;
    ghostBtn->normalRec = { 530,295,66,28 };
    ghostBtn->focusedRec = { 530,322,66,28 };
    ghostBtn->pressedRec = { 530,295,66,28 };

    gargoyleBtn = (GuiButton*)CreateGuiButton(7, app->guiManager, this, { app->render->camera.x + 930 + 35,app->render->camera.y + 460 + 125,102,28 }, "Gargoyle selected");
    gargoyleBtn->texture = app->guiManager->battleBox;
    gargoyleBtn->normalRec = { 600,295,102,28 };
    gargoyleBtn->focusedRec = { 600,322,102,28 };
    gargoyleBtn->pressedRec = { 600,295,102,28 };
    return true;
}

bool BattlePanel::Update(float dt, bool doLogic)
{
    GuiPanel::Update(dt, doLogic);
    return true;
}

bool BattlePanel::Draw()
{
    app->render->DrawTexture(app->guiManager->battleBox, -app->render->camera.x + 150, -app->render->camera.y + 460, &charBox);
    app->render->DrawTexture(app->guiManager->battleBox, -app->render->camera.x + 480, -app->render->camera.y + 460, &actionBox);
    app->render->DrawTexture(app->guiManager->battleBox, -app->render->camera.x + 930, -app->render->camera.y + 460, &enemyBox);
    app->render->DrawTexture(app->guiManager->battleBox, -app->render->camera.x + 460, -app->render->camera.y + 460 + 95, &arrow);

    switch (charArrow)
    {
    case 0:
        app->render->DrawTexture(app->guiManager->battleBox, -app->render->camera.x + 150 + 19, -app->render->camera.y + 460 + 20, &arrow);
        break;
    case 1:
        app->render->DrawTexture(app->guiManager->battleBox, -app->render->camera.x + 150 + 19, -app->render->camera.y + 460 + 95, &arrow);
        break;
    }

    switch (actionArrow)
    {
    case 0:
        app->render->DrawTexture(app->guiManager->battleBox, -app->render->camera.x + 480 + 19, -app->render->camera.y + 460 + 20, &arrow);
        break;
    case 1:
        app->render->DrawTexture(app->guiManager->battleBox, -app->render->camera.x + 480 + 19, -app->render->camera.y + 460 + 70, &arrow);
        break;
    case 2:
        app->render->DrawTexture(app->guiManager->battleBox, -app->render->camera.x + 480 + 19, -app->render->camera.y + 460 + 120, &arrow);
        break;
    }

    switch (enemyArrow)
    {
    case 0:
        app->render->DrawTexture(app->guiManager->battleBox, -app->render->camera.x + 930 + 19, -app->render->camera.y + 460 + 20, &arrow);
        break;
    case 1:
        app->render->DrawTexture(app->guiManager->battleBox, -app->render->camera.x + 930 + 19, -app->render->camera.y + 460 + 70, &arrow);
        break;
    case 2:
        app->render->DrawTexture(app->guiManager->battleBox, -app->render->camera.x + 930 + 19, -app->render->camera.y + 460 + 120, &arrow);
        break;
    }

    GuiPanel::Draw();
    return true;
}

bool BattlePanel::CleanUp()
{
    app->guiManager->quitPanel->Disable();
    return true;
}

bool BattlePanel::OnGuiMouseClickEvent(GuiControl* control)
{
    if (control->id == ChamanBtn->id)
    {
        charArrow = 0;
    }
    else if (control->id == PaladinBtn->id)
    {
        charArrow = 1;
    }

    if (control->id == attackBtn->id)
    {
        actionArrow = 0;
    }
    else if (control->id == dodgeBtn->id)
    {
        actionArrow = 1;
    }
    else if (control->id == runBtn->id)
    {
        actionArrow = 2;
    }

    if (control->id == fallenAngelBtn->id)
    {
        enemyArrow = 0;
    }
    else if (control->id == ghostBtn->id)
    {
        enemyArrow = 1;
    }
    else if (control->id == gargoyleBtn->id)
    {
        enemyArrow = 2;
    }

    return true;
}
