#include "QuestPanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "TitleScreen.h"

QuestPanel::QuestPanel(bool active) : GuiPanel(active)
{
    Active = active;
}

QuestPanel::~QuestPanel()
{
}

bool QuestPanel::Start()
{

    return true;
}

bool QuestPanel::Update(float dt, bool doLogic)
{
    GuiPanel::Update(dt, doLogic);
    return true;
}

bool QuestPanel::Draw()
{
    app->render->DrawTexture(app->guiManager->questScreen, -app->render->camera.x, -app->render->camera.y, NULL, true);
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

    return true;
}
