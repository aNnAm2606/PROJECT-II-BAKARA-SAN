#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeToBlack.h"
#include "TutorialScene_4.h"
#include "GuiManager.h"
#include "PlayerModule.h"
#include "Point.h"

#include "Defs.h"
#include "Log.h"

TutorialScene_4::TutorialScene_4(bool startEnabled) : Module(startEnabled)
{
	name.Create("StartForestScene");
}

// Destructor
TutorialScene_4::~TutorialScene_4()
{}

// Called before render is available
bool TutorialScene_4::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool TutorialScene_4::Start()
{
	app->render->camera.x = -400;
	app->render->camera.y = -150;

	tutorialScene_4 = app->tex->Load("Assets/Art/Maps/tutorial_map_4.png");

	app->playerModule->SetPosition(1600, 450);
	return true;
}

// Called each loop iteration
bool TutorialScene_4::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool TutorialScene_4::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y -= app->render->cameraSpeed;

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += app->render->cameraSpeed;


	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= app->render->cameraSpeed;


	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += app->render->cameraSpeed;


	app->render->DrawTexture(tutorialScene_4, 0, 0, NULL);


	return true;
}

// Called each loop iteration
bool TutorialScene_4::PostUpdate()
{
	bool ret = true;
	app->playerModule->GetPosition(playerPos.x, playerPos.y);
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		app->guiManager->pausePanel->Enable();
	if (playerPos.x > 1700)app->fade->Fade(this, (Module*)app->tutorialForestScene);


	return ret;
}

// Called before quitting
bool TutorialScene_4::CleanUp()
{
	LOG("Freeing scene");
	app->tex->UnLoad(tutorialScene_4);
	app->guiManager->pausePanel->Disable();

	return true;
}