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
	app->render->camera.x = 0;
	app->render->camera.y = -200;

	startForestScene = app->tex->Load("Assets/Art/Maps/forest_map.png");

	app->playerModule->Enable();
	app->playerModule->SetPosition(0, -200);
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
	

	return true;
}

// Called each loop iteration
bool StartForestScene::PostUpdate()
{
	bool ret = true;
	app->playerModule->GetPosition(playerPos.x, playerPos.y);
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		app->guiManager->pausePanel->Enable();
	if(playerPos.y < -200)app->fade->Fade(this, (Module*)app->townScene);
	 

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