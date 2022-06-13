#include "BattlePanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "TitleScreen.h"
#include "BattleScene.h"
#include "Window.h"
#include "Fonts.h"
#include "Character.h"
#include "Ability.h"

#include <iostream>

BattlePanel::BattlePanel(bool active) : GuiPanel(active)
{
    Active = active;

    big_box = { 554, 0, 307, 208 };
    medium_box = { 331,0,205,208 };
    small_box = { 0, 0, 145, 208 };
    arrow = { 410, 210, 16, 36 };
}

BattlePanel::~BattlePanel()
{
}

bool BattlePanel::Start()
{
    app->win->GetWindowSize(swidth, sheight);

    const char* format = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz";
    m_BaseFont = app->fonts->Load("Assets/Fonts/rune_font_base.png", format);
    m_HighlightFont = app->fonts->Load("Assets/Fonts/rune_font_highlight.png", format);
    m_PressFont = app->fonts->Load("Assets/Fonts/rune_font_press.png", format);

    return true;
}

bool BattlePanel::Update(float dt, bool doLogic)
{
    GuiPanel::Update(dt, doLogic);

    for (size_t i = 0; i < m_Buttons.size(); i++) {
        m_Buttons[i].Update();
        
        if (m_Buttons[i].clicked) {
            app->battleScene->SelectedAbility(i);
            Disable();
            break;
        }
    }

    return true;
}

bool BattlePanel::Draw()
{   
    app->render->DrawTexture(app->guiManager->battleBox, swidth - 250, 50, &medium_box);

    std::string name = "";
    name += character->GetCharacterName();

    app->fonts->BlitText(swidth - 200, 60, m_BaseFont, name.c_str());

    app->render->DrawTexture(app->guiManager->battleBox, swidth - 250, 258, &medium_box);

    for (size_t i = 0; i < m_Buttons.size(); i++) {
        m_Buttons[i].Draw();
    }

    /*app->render->DrawTexture(app->guiManager->battleBox, -app->render->camera.x + 480, -app->render->camera.y + 460, &actionBox);
    app->render->DrawTexture(app->guiManager->battleBox, -app->render->camera.x + 930, -app->render->camera.y + 460, &enemyBox);
    app->render->DrawTexture(app->guiManager->battleBox, -app->render->camera.x + 460, -app->render->camera.y + 460 + 95, &arrow);*/

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
    return true;
}

void BattlePanel::OnEnable()
{
    character = app->battleScene->GetActiveCharacter();
    abilities = character->GetAbilities();

    m_Buttons.clear();

    SDL_Rect rect = {
        swidth - 250,
        258,
        200,
        8
    };

    for (size_t i = 0; i < abilities->size(); i++) {
        rect.y += rect.h + 10;
        m_Buttons.push_back(Button(rect, (SDL_Texture*)NULL, abilities->at(i)->GetAbilityName(), m_BaseFont));
        m_Buttons[i].SetFontStates(m_BaseFont, m_HighlightFont, m_PressFont);
    }
}

void BattlePanel::OnDisable()
{
    
}
