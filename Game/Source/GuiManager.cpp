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

GuiManager::GuiManager(bool startEnabled) : Module(startEnabled)
{
	name.Create("guiManager");
}

GuiManager::~GuiManager() {}

bool GuiManager::Awake(pugi::xml_node&)
{
	return true;
}

bool GuiManager::Start()
{
	// Panel Images
	titleButtons = app->tex->Load("Assets/Art/GUI/titleButtons.png");
	settingsBox = app->tex->Load("Assets/Art/GUI/settingsBox.png");
	quitBox = app->tex->Load("Assets/Art/GUI/exitBox.png");
	credits = app->tex->Load("Assets/Art/GUI/credits.png");
	pauseBox = app->tex->Load("Assets/Art/GUI/pauseBox.png");
	battleBox = app->tex->Load("Assets/Art/GUI/battleUI.png");
	loseScreen = app->tex->Load("Assets/Art/GUI/loseScreen.png");
	victoryScreen = app->tex->Load("Assets/Art/GUI/winScreen.png");

	// Audio for buttons
	//app->audio->LoadFx("Assets/audio/fx/buttonFocus.wav");
	//app->audio->LoadFx("Assets/audio/fx/buttonPressed.wav");

	debug = false;

	titlePanel = new TitlePanel(false);
	settingsPanel = new SettingsPanel(false);
	quitPanel = new QuitPanel(false);
	creditsPanel = new Credits(false);
	pausePanel = new PausePanel(false);
	battlePanel = new BattlePanel(false);
	losePanel = new LosePanel(false);
	victoryPanel = new VictoryPanel(false);

	panels.add(titlePanel);
	panels.add(settingsPanel);
	panels.add(quitPanel);
	panels.add(creditsPanel);
	panels.add(pausePanel);
	panels.add(battlePanel);
	panels.add(losePanel);
	panels.add(victoryPanel);

	//init panels
	p2ListItem<GuiPanel*>* panel = panels.start;

	while (panel != nullptr)
	{
		panel->data->Start();
		panel = panel->next;
	}


	return true;
}


bool GuiManager::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if (app->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN)
		battlePanel->Disable();

	if (app->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN)
		victoryPanel->Enable();
	if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
		victoryPanel->Disable();

	if (app->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
		losePanel->Enable();
	if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
		losePanel->Disable();

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		app->guiManager->pausePanel->gamePaused = !app->guiManager->pausePanel->gamePaused;
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && app->guiManager->settingsPanel->GetActive() == true)
		app->guiManager->settingsPanel->Disable();

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
	settingsBox = nullptr;
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






