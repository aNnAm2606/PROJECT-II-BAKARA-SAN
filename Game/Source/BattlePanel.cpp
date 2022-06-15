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
#include "Color.h"

#include <iostream>

BattlePanel::BattlePanel(bool active) : GuiPanel(active)
{
    Active = active;

    big_box = { 554, 0, 307, 208 };
    medium_box = { 331,0,205,208 };
    small_box = { 0, 0, 145, 208 };
    arrow = { 410, 210, 16, 36 };

    m_LabelColor = { 0,0,0 };

    m_BaseColor = {85,85,85};
    m_HighlightColor = { 240,240,240 };
    m_PressColor = {50,50,50};
}

BattlePanel::~BattlePanel()
{
}

bool BattlePanel::Start()
{
    app->win->GetWindowSize(swidth, sheight);

    //char format[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz " };
    char format[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };

    m_LabelFont = app->fonts->Load("Assets/Fonts/rtype_font3.png", format, 2, m_LabelColor);
    m_BaseFont = app->fonts->Load("Assets/Fonts/rtype_font3.png", format, 2, m_BaseColor);
    m_HighlightFont = app->fonts->Load("Assets/Fonts/rtype_font3.png", format, 2, m_HighlightColor);
    m_PressFont = app->fonts->Load("Assets/Fonts/rtype_font3.png", format, 2, m_PressColor);

    /*m_BaseFont = app->fonts->Load("Assets/Fonts/rune_font_base.png", format);
    m_HighlightFont = app->fonts->Load("Assets/Fonts/rune_font_highlight.png", format);
    m_PressFont = app->fonts->Load("Assets/Fonts/rune_font_press.png", format);*/

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
    app->render->DrawTexture(app->guiManager->battleBox, swidth - 250, 50, &medium_box, false);
    app->render->DrawTexture(app->guiManager->battleBox, swidth - 250, 258, &medium_box, false);

    std::string name = "";
    name += character->GetCharacterName();
    app->fonts->BlitText(swidth - 180, 80, m_LabelFont, name.c_str(), false);

    // Health
    app->fonts->BlitText(swidth - 230, 110, m_LabelFont, "hp", false);
    std::string health = "";
    health += std::to_string(character->GetHealth());
    health += "/";
    health += std::to_string(character->GetMaxHealth());
    app->fonts->BlitText(swidth - 200, 110, m_BaseFont, health.c_str(), false);

    // Damage
    std::string damage = std::to_string(character->GetDamage());
    app->fonts->BlitText(swidth - 230, 130, m_LabelFont, "damage", false);
    app->fonts->BlitText(swidth - 160, 130, m_BaseFont, damage.c_str(), false);

    // Speed
    std::string speed = std::to_string(character->GetSpeed());
    app->fonts->BlitText(swidth - 230, 150, m_LabelFont, "speed", false);
    app->fonts->BlitText(swidth - 160, 150, m_BaseFont, speed.c_str(), false);
    
    // Abilities
    app->fonts->BlitText(swidth - 190, 280, m_LabelFont, "abilities", false);
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
        280,
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
