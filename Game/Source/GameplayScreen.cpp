#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "GameplaySceen.h"
#include "FadeToBlack.h"
#include "GuiManager.h"
#include "Transitions.h"

#include "Defs.h"
#include "Log.h"

GameplayScreen::GameplayScreen(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer) :
	Scene(startEnabled, playerEnabled, name, cameraPos, playerPos, followPlayer)
{
	
}

// Destructor
GameplayScreen::~GameplayScreen()
{
	Scene::~Scene();
}

// Called before render is available
bool GameplayScreen::Awake(pugi::xml_node& config)
{
	Scene::Awake(config);
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool GameplayScreen::Start()
{
	Scene::Start();
	sceneTexture = app->tex->Load("Assets/Art/Maps/tutorial_map_part1.png");

	return true;
}

// Called each loop iteration
bool GameplayScreen::PreUpdate()
{
	Scene::PreUpdate();
	return true;
}

// Called each loop iteration
bool GameplayScreen::Update(float dt)
{
	Scene::Update(dt);

	

	return true;
}

// Called each loop iteration
bool GameplayScreen::PostUpdate()
{
	Scene::PostUpdate();
	bool ret = true;
	GamePad& gamepad = app->input->pads[0];
	if(app->input->GamepadConnected() == false)
	{
		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		{
			app->guiManager->pausePanel->Enable();
		}
	}
	else if(gamepad.start == true) app->guiManager->pausePanel->Enable();
	
	if (app->guiManager->back2Title == true)
	{
		app->transitions->SelectTransition(1, 0, 1280, this, (Module*)app->titleScreen);
		app->guiManager->back2Title = false;
	}
	return ret;
}

// Called before quitting
bool GameplayScreen::CleanUp()
{
	Scene::CleanUp();
	LOG("Freeing scene");
	
	app->guiManager->settingsPanel->Disable();
	app->guiManager->pausePanel->Disable();
	return true;
}
