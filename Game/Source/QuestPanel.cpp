#include "QuestPanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "TitleScreen.h"
#include "Textures.h"
#include "QuestModule.h"
#include "Fonts.h"
#include "Quest.h"

QuestPanel::QuestPanel(bool active) : GuiPanel(active)
{
    Active = active;

    m_LabelColor = { 0,0,0 };

    m_BaseColor = { 85,85,85 };
    m_HighlightColor = { 180,180,180 };
    m_PressColor = { 112,69,0 };
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

    char format[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
    m_LabelFont = app->fonts->Load("Assets/Fonts/rtype_font3.png", format, 2, m_LabelColor);
    m_BaseFont = app->fonts->Load("Assets/Fonts/rtype_font3.png", format, 2, m_BaseColor);
    m_HighlightFont = app->fonts->Load("Assets/Fonts/rtype_font3.png", format, 2, m_HighlightColor);
    m_PressFont = app->fonts->Load("Assets/Fonts/rtype_font3.png", format, 2, m_PressColor);

    m_ItemsTexture = app->tex->Load("Assets/Art/Items/items.png");

    m_QuestOffset = { 100, 153 };
    m_QuestSpacing = 75;

    m_QuestInfoOffset = { 761 + 40, 156 + 20 };
    m_QuestRewardsOffset = { 803, 386 };
    m_QuestRewardsSpacing = 88;

    m_Quests = app->quests->GetQuestList();

    m_SelectedQuest = 0;

    return true;
}

bool QuestPanel::Update(float dt, bool doLogic)
{
    GuiPanel::Update(dt, doLogic);

    for (size_t i = 0; i < m_Buttons.size(); i++) {
        m_Buttons[i].Update();

        if (m_Buttons[i].clicked) {
            m_Buttons[m_SelectedQuest].SetFont(m_LabelFont);
            m_SelectedQuest = i;
            m_Buttons[i].SetFont(m_PressFont);

            m_Buttons[i].clicked = false;
        }
    }

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

    // Draw quests
    for (size_t i = 0; i < m_Buttons.size(); i++) {
        m_Buttons[i].Draw();
    }

    if (m_QuestIds.size() > 0) {
        Quest* q = m_Quests[m_QuestIds[m_SelectedQuest]];

        app->fonts->BlitText(m_QuestInfoOffset.x, m_QuestInfoOffset.y, m_LabelFont, q->getTitle(), false);
        app->fonts->BlitText(m_QuestInfoOffset.x + 15, m_QuestInfoOffset.y + 25, m_BaseFont, q->getDesc(), false);
        std::string ptext = "progress ";
        ptext += q->GetProgress();
        app->fonts->BlitText(m_QuestInfoOffset.x + 15, m_QuestInfoOffset.y + 45, m_PressFont, ptext.c_str(), false);

        Item::EItemType* rewards = q->GetRewards();

        int r_count = 0;
        SDL_Rect rect{
            0, 0,
            32, 32
        };
        for (int i = 0; i < 4; i++) {
            if (rewards[i] != Item::EItemType::EITEMTYPE_NONE) {
                rect.x = rewards[i] % 6 * 35;
                rect.y = rewards[i] / 6 * 35;

                app->render->DrawTextureScaled(m_ItemsTexture, m_QuestRewardsOffset.x + m_QuestRewardsSpacing * r_count, m_QuestRewardsOffset.y, 75, 72, &rect, false);
                r_count++;
            }
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

void QuestPanel::OnEnable()
{
    m_QuestIds.clear();
    m_Buttons.clear();
    SDL_Rect rect = {
        m_QuestOffset.x,
        m_QuestOffset.y,
        633,
        56,
    };

    int q_count = 0;
    for (size_t i = 0; i < QuestModule::EQuest::EQUEST_NONE; i++) {
        Quest* q = m_Quests[i];

        if (!q) continue;

        m_QuestIds.push_back(i);

        rect.y = m_QuestOffset.y + m_QuestSpacing * q_count;

        m_Buttons.push_back(Button(rect, (SDL_Texture*)NULL, q->getTitle(), m_LabelFont));
        m_Buttons[q_count].SetFontStates(m_LabelFont, m_HighlightFont, m_PressFont);
        q_count++;
    }

    m_SelectedQuest = 0;
    if (m_Buttons.size() > 0) {
        m_Buttons[0].SetFont(m_PressFont);
    }
}