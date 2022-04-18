#include "GuiManager.h"
#include "App.h"
#include "Textures.h"
#include "Window.h"
#include "Render.h"
#include "Audio.h"

//add all panels here
#include "TitlePanel.h"
//#include "SettingsPanel.h"
//#include "ExitPanel.h"


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
	// Textures
	titleButtons = app->tex->Load("Assets/Art/GUI/titleButtons.png");

	// Texture Panels
	//settingsBox = app->tex->Load("Assets/Sprites/UI/smallPanel.png");
	//exitBox = app->tex->Load("Assets/Sprites/UI/mediumPanel.png");

	// Audio for buttons
	//app->audio->LoadFx("Assets/audio/fx/buttonFocus.wav");
	//app->audio->LoadFx("Assets/audio/fx/buttonPressed.wav");

	Debug = false;

	titlePanel = new TitlePanel(false);
	//settingsPanel = new SettingsPanel(false);
	//exitPanel = new ExitPanel(false);

	panels.add(titlePanel);
	//panels.add(settingsPanel);
	//panels.add(exitPanel);

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

	if (app->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN)
		titlePanel->Active = !titlePanel->GetActive();
	//if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
	//	settingsPanel->Active = !settingsPanel->GetActive();
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
	exitBox = nullptr;

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






