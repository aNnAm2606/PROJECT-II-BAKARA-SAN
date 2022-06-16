#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "EndScreen.h"
#include "FadeToBlack.h"
#include "GuiManager.h"
#include "Transitions.h"
#include "BattleScene.h"

#include "Defs.h"
#include "Log.h"

EndScreen::EndScreen(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer)
	: Scene(startEnabled, playerEnabled, name, cameraPos, playerPos, followPlayer)
{
	
}

// Destructor
EndScreen::~EndScreen()
{
	Scene::~Scene();
}

// Called before render is available
bool EndScreen::Awake(pugi::xml_node& config)
{
	Scene::Awake(config);
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool EndScreen::Start()
{
	Scene::Start();
	
	if (app->battleScene->Lost()) {
		app->guiManager->losePanel->Enable();
	}
	else {
		app->guiManager->victoryPanel->Enable();
	}

	app->currentScene = sceneID::END;
	return true;
}

// Called each loop iteration
bool EndScreen::PreUpdate()
{
	Scene::PreUpdate();

	return true;
}

// Called each loop iteration
bool EndScreen::Update(float dt)
{
	Scene::Update(dt);

	if (count > 90) app->fade->Fade(this, (Module*)app->titleScreen);
	else count++;

	return true;
}

// Called each loop iteration
bool EndScreen::PostUpdate()
{
	Scene::PostUpdate();
	bool ret = true;
	GamePad& gamepad = app->input->pads[0];
	if (app->input->GamepadConnected() == false)
	{
		//if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) app->fade->Fade(this, (Module*)app->titleScreen);
	}
	else if(gamepad.a == true) app->fade->Fade(this, (Module*)app->titleScreen);
		
	if (app->guiManager->back2Title == true)
	{
		app->transitions->SelectTransition(1, 0, 1280, this, (Module*)app->titleScreen);
		app->guiManager->back2Title = false;
	}

	return ret;
}

// Called before quitting
bool EndScreen::CleanUp()
{
	Scene::CleanUp();
	
	if (app->battleScene->Lost()) {
		app->guiManager->losePanel->Disable();
	}
	else {
		app->guiManager->victoryPanel->Disable();
	}

	remove("save_game.xml");

	LOG("Freeing scene");

	return true;
}
