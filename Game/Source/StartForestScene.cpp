#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeToBlack.h"
#include "StartForestScene.h"
#include "GuiManager.h"
#include "PlayerModule.h"
#include "Point.h"

#include "Defs.h"
#include "Log.h"

StartForestScene::StartForestScene(bool startEnabled) : Module(startEnabled)
{
	name.Create("StartForestScene");
}

// Destructor
StartForestScene::~StartForestScene()
{}

// Called before render is available
bool StartForestScene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool StartForestScene::Start()
{
	app->render->camera.x = 100;
	app->render->camera.y = -200;

	startForestScene = app->tex->Load("Assets/Art/Maps/forest_map.png");
	app->audio->PlayMusic("Assets/Audio/Music/world_map.ogg");

	app->playerModule->Enable();
	app->playerModule->SetPosition(700, 550);
	app->render->followPlayerX = true;
	app->render->followPlayerY = true;

	app->currentScene = sceneID::START_FOREST;
	app->SceneLoadFinish();
	return true;
}

// Called each loop iteration
bool StartForestScene::PreUpdate()
{
	
	return true;
}

// Called each loop iteration
bool StartForestScene::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y -= app->render->cameraSpeed;

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += app->render->cameraSpeed;


	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= app->render->cameraSpeed;


	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += app->render->cameraSpeed;


	app->render->DrawTexture(startForestScene, 0, 0, NULL);
	app->playerModule->GetPosition(playerPos.x, playerPos.y);
	if (playerPos.x < 700 || playerPos.x > 1250) app->render->followPlayerX = false;
	
	else app->render->followPlayerX = true;
	if (playerPos.y < 375 || playerPos.y > 700) app->render->followPlayerY = false;
	else app->render->followPlayerY = true;

	return true;
}

// Called each loop iteration
bool StartForestScene::PostUpdate()
{
	bool ret = true;

	if(playerPos.y < -200) app->fade->Fade(this, (Module*)app->townScene);
	 

	return ret;
}

// Called before quitting
bool StartForestScene::CleanUp()
{
	LOG("Freeing scene");
	app->tex->UnLoad(startForestScene);
	app->guiManager->pausePanel->Disable();

	return true;
}