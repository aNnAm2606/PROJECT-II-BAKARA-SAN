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

GuiManager::GuiManager() :Module()
{
	name.Create("gui manager");
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

	// Audio for buttons
	//app->audio->LoadFx("Assets/audio/fx/buttonFocus.wav");
	//app->audio->LoadFx("Assets/audio/fx/buttonPressed.wav");

	Debug = false;

	titlePanel = new TitlePanel(false);
	settingsPanel = new SettingsPanel(false);
	quitPanel = new QuitPanel(false);
	creditsPanel = new Credits(false);

	panels.add(titlePanel);
	panels.add(settingsPanel);
	panels.add(quitPanel);
	panels.add(creditsPanel);

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

	//if (app->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
	//	pausePanel->Active = !pausePanel->GetActive();
	//if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	//	exitPanel->Active = !exitPanel->GetActive();

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		Debug = !Debug;

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

bool GuiManager::PostUpdate() {

	p2ListItem<GuiPanel*>* panel = panels.start;

	while (panel != nullptr)
	{
		if(panel->data->Active)
			panel->data->Draw();
		
		panel = panel->next;
	}

	return true;

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






