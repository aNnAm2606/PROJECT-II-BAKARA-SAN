#include "GuiManager.h"
#include "App.h"
#include "Textures.h"
#include "Window.h"
#include "Render.h"
#include "Audio.h"

// Panels.h
#include "TitlePanel.h"
#include "SettingsPanel.h"
#include "QuitPanel.h"
#include "Credits.h"
#include "PausePanel.h"
#include "BattlePanel.h"
#include "LosePanel.h"
#include "VictoryPanel.h"
#include "InventoryPanel.h"
#include "PartyPanel.h"
#include "QuestPanel.h"
#include "BattleScene.h"
#include "LogoScreen.h"
#include "TitleScreen.h"
#include "EndScreen.h"

GuiManager::GuiManager(bool startEnabled) : Module(startEnabled)
{
	name.Create("guiManager");
}

GuiManager::~GuiManager()
{

}

bool GuiManager::Awake(pugi::xml_node&)
{
	return true;
}

bool GuiManager::Start()
{
	// Panel Images
	titleButtons = app->tex->Load("Assets/Art/GUI/titleButtons.png");
	boxSettings = app->tex->Load("Assets/Art/GUI/boxSettings.png");
	quitBox = app->tex->Load("Assets/Art/GUI/exitBox.png");
	credits = app->tex->Load("Assets/Art/GUI/credits.png");
	pauseBox = app->tex->Load("Assets/Art/GUI/pauseBox.png");
	battleBox = app->tex->Load("Assets/Art/GUI/battleUI2.png");
	loseScreen = app->tex->Load("Assets/Art/GUI/loseScreen.png");
	victoryScreen = app->tex->Load("Assets/Art/GUI/winScreen.png");
	questScreen = app->tex->Load("Assets/Art/GUI/questUI.png");
	inventoryScreen = app->tex->Load("Assets/Art/GUI/inventoryUI.png");
	partyScreen = app->tex->Load("Assets/Art/GUI/partyUI.png");
	lose_fx = app->audio->LoadFx("Assets/Audio/Fx/GAME_OVER.wav");
	Win_fx = app->audio->LoadFx("Assets/Audio/Fx/level_up.wav");

	// Audio for buttons
	//app->audio->LoadFx("Assets/audio/fx/buttonFocus.wav");
	//app->audio->LoadFx("Assets/audio/fx/buttonPressed.wav");
	Close_FX = app->audio->LoadFx("Assets/Audio/Fx/UI_CloseMenu.wav");
	Open_FX = app->audio->LoadFx("Assets/Audio/Fx/UI_openMenu.wav");
	debug = false;
	cursorMode = false;
	settings = false;
	pause = false;
	cursor = 0;

	titlePanel = new TitlePanel(false);
	settingsPanel = new SettingsPanel(false);
	quitPanel = new QuitPanel(false);
	creditsPanel = new Credits(false);
	pausePanel = new PausePanel(false);
	battlePanel = new BattlePanel(false);
	losePanel = new LosePanel(false);
	victoryPanel = new VictoryPanel(false);
	questPanel = new QuestPanel(false);
	inventoryPanel = new InventoryPanel(false);
	partyPanel = new PartyPanel(false);

	panels.add(titlePanel);
	panels.add(settingsPanel);
	panels.add(quitPanel);
	panels.add(creditsPanel);
	panels.add(pausePanel);
	panels.add(battlePanel);
	panels.add(losePanel);
	panels.add(victoryPanel);
	panels.add(questPanel);
	panels.add(inventoryPanel);
	panels.add(partyPanel);

	//init panels
	p2ListItem<GuiPanel*>* panel = panels.start;

	while (panel != nullptr)
	{
		panel->data->Start();
		panel = panel->next;
	}

	rect1 = { 603,352,66,27 };
	rect2 = { 587,326,190,90 };
	rect3 = { 560,307,259,132 };
	rect4 = { 503,258,397,237 };
	rect5 = { 432,203,602,360 };
	rect6 = { 282,155,851,443 };
	rect7 = { 227,129,966,516 };
	rect8 = { 124,104,1108,550 };
	rect9 = { 61,57,1191,623 };

	return true;
}

bool GuiManager::Update(float dt)
{
	GamePad& gamepad = app->input->pads[0];
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	// Pause / panels
	if (CanOpenSettings()) {
		if (!inventoryPanel->GetActive() && !partyPanel->GetActive() && !questPanel->GetActive()) {
			if (app->input->GamepadConnected() == false)
			{
				if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
					if (app->guiManager->pausePanel->gamePaused == false) app->audio->PlayFx(Open_FX);
					else if (app->guiManager->pausePanel->gamePaused == true) app->audio->PlayFx(Close_FX);
					app->guiManager->pausePanel->gamePaused = !app->guiManager->pausePanel->gamePaused;
				}
				if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && app->guiManager->settingsPanel->GetActive() == true) {
					app->audio->PlayFx(Close_FX);
					app->guiManager->settingsPanel->Disable();
				}
			}
			else
			{
				if (gamepad.start == true)
				{
					if (app->guiManager->pausePanel->gamePaused == false) app->audio->PlayFx(Open_FX);
					else if (app->guiManager->pausePanel->gamePaused == true) app->audio->PlayFx(Close_FX);
					app->guiManager->pausePanel->gamePaused = !app->guiManager->pausePanel->gamePaused;
				}
				if (gamepad.start == true && app->guiManager->settingsPanel->GetActive() == true) {
					app->audio->PlayFx(Close_FX);
					app->guiManager->settingsPanel->Disable();
				}
			}
		}
		else {
			if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
				cursorMode = false;
			}
		}
	}

	if (CanOpenPanels()) {

		// BasePanels
		if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN) {
			if (cursorMode) {
				if (cursor == 2) {
					cursorMode = false;
				}
			}
			else {
				cursorMode = true;
			}

			cursor = 2;
		}

		if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) {
			if (cursorMode) {
				if (cursor == 0) {
					cursorMode = false;
				}
			}
			else {
				cursorMode = true;
			}

			cursor = 0;
		}

		if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
			if (cursorMode) {
				if (cursor == 1) {
					cursorMode = false;
				}
			}
			else {
				cursorMode = true;
			}

			cursor = 1;
		}

		if (cursorMode == true)
		{
			if (anim != 9)
			{
				timer++;
				if (timer >= 1)
				{
					anim++;
					timer = 0;
				}
			}
			if (anim >= 9) anim = 9;

			if (app->input->GetKey(SDL_SCANCODE_L) == KeyState::KEY_DOWN) cursor = cursor + 1;
			if (app->input->GetKey(SDL_SCANCODE_J) == KeyState::KEY_DOWN) cursor = cursor - 1;

			switch (cursor)
			{
			case 0:
				inventoryPanel->Disable();
				partyPanel->Disable();
				questPanel->Enable();
				break;
			case 1:
				inventoryPanel->Disable();
				questPanel->Disable();
				partyPanel->Enable();
				break;
			case 2:
				questPanel->Disable();
				partyPanel->Disable();
				inventoryPanel->Enable();
				break;
			}

			if (cursor > 2) cursor = 0;
			if (cursor < 0) cursor = 2;
		}
		else
		{
			if (anim != 0)
			{
				timer++;
				if (timer >= 1)
				{
					anim--;
					timer = 0;
				}
			}

			if (anim <= 0)
			{
				anim = 0;
				inventoryPanel->Disable();
				partyPanel->Disable();
				questPanel->Disable();
			}
		}
	}
	
	if (app->guiManager->pausePanel->gamePaused == true
		&& app->guiManager->settingsPanel->GetActive() == false
		&& app->guiManager->quitPanel->GetActive() == false)
		app->guiManager->pausePanel->Enable();
	else if (app->guiManager->pausePanel->gamePaused == false
		&& app->guiManager->settingsPanel->GetActive() == false 
		&& app->guiManager->quitPanel->GetActive() == false)
		app->guiManager->pausePanel->Disable();
	
	accumulatedTime += dt;
	if (accumulatedTime >= updateMsCycle) doLogic = true;

	UpdateAll(dt,doLogic);

	if (doLogic == true)
	{
		accumulatedTime = 0.0f;
		doLogic = false;
	}
	
	return true;
}

bool GuiManager::UpdateAll(float dt, bool doLogic) {

	p2ListItem<GuiPanel*>* panel = panels.start;

	while (panel != nullptr )
	{
		if(panel->data->Active)
			panel->data->Update( dt, doLogic);
		
		panel = panel->next;
	}

	return true; 

}

bool GuiManager::PostUpdate() 
{
	bool ret = true;

	p2ListItem<GuiPanel*>* panel = panels.start;

	while (panel != nullptr)
	{
		if(panel->data->Active)
			panel->data->Draw();
		
		panel = panel->next;
	}

	if (app->guiManager->quitPanel->closeGame == true)
		ret = false;

	return ret;

}

bool GuiManager::CleanUp()
{
	p2ListItem<GuiPanel*>* panel = panels.start;

	while (panel != nullptr)
	{
		panel->data->CleanUp();
		panel = panel->next;
	}

	panels.clear();

	titleButtons = nullptr;
	boxSettings = nullptr;
	quitBox = nullptr;
	credits = nullptr;
	pauseBox = nullptr;

	return true;
}

void GuiManager::OpenPanel(int panel_id)
{
	p2ListItem<GuiPanel*>* panel = panels.start;
	
	while (panel != nullptr)
	{
		if (panel->data->id == panel_id)
		{
			panel->data->Enable();
			break;
		}
		panel = panel->next;
	}
}

bool GuiManager::OnGuiMouseClickEvent(GuiControl* control)
{

	p2ListItem<GuiPanel*>* panel = panels.start;

	while (panel != nullptr)
	{
		if (control->parent == panel->data && panel->data->Active)
		{
			panel->data->OnGuiMouseClickEvent(control);
		}
		panel = panel->next;
	}

	return true;
}

bool GuiManager::CanOpenPanels()
{
	bool canOpen = true;

	canOpen = canOpen && !app->battleScene->IsEnabled();
	canOpen = canOpen && !app->logoScreen->IsEnabled();
	canOpen = canOpen && !app->titleScreen->IsEnabled();
	canOpen = canOpen && !app->endScreen->IsEnabled();

	return canOpen;
}

bool GuiManager::CanOpenSettings()
{
	bool canOpen = true;

	canOpen = canOpen && !app->logoScreen->IsEnabled();
	canOpen = canOpen && !app->titleScreen->IsEnabled();
	canOpen = canOpen && !app->endScreen->IsEnabled();

	return canOpen;
}
