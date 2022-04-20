#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeToBlack.h"
#include "TutorialForestScene.h"
#include "GuiManager.h"
#include "PlayerModule.h"
#include "Point.h"

#include "Defs.h"
#include "Log.h"

TutorialForestScene::TutorialForestScene(bool startEnabled) : Module(startEnabled)
{
	name.Create("StartForestScene");
}

// Destructor
TutorialForestScene::~TutorialForestScene()
{}

// Called before render is available
bool TutorialForestScene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool TutorialForestScene::Start()
{
	app->render->camera.x = -600;
	app->render->camera.y = -150;
	app->playerModule->SetPosition(1700, 600);
	tutorialForestScene = app->tex->Load("Assets/Art/Maps/out_of_tutorial_map.png");
	return true;
}

// Called each loop iteration
bool TutorialForestScene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool TutorialForestScene::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y -= app->render->cameraSpeed;

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += app->render->cameraSpeed;


	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= app->render->cameraSpeed;


	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += app->render->cameraSpeed;

	app->render->DrawTexture(tutorialForestScene, 0, 0, NULL);
	
	return true;
}

// Called each loop iteration
bool TutorialForestScene::PostUpdate()
{
	bool ret = true;
	app->playerModule->GetPosition(playerPos.x, playerPos.y);
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		app->guiManager->pausePanel->Enable();
	if (playerPos.x > 1800)app->fade->Fade(this, (Module*)app->townScene);

	return ret;
}

// Called before quitting
bool TutorialForestScene::CleanUp()
{
	LOG("Freeing scene");
	app->tex->UnLoad(tutorialForestScene);
	return true;
}
