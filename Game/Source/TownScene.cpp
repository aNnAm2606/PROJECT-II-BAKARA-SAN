#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeToBlack.h"
#include "TownScene.h"
#include "GuiManager.h"
#include "PlayerModule.h"

#include "Defs.h"
#include "Log.h"

TownScene::TownScene(bool startEnabled) : Module(startEnabled)
{
	name.Create("TownScene");
}

// Destructor
TownScene::~TownScene()
{}

// Called before render is available
bool TownScene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool TownScene::Start()
{
	app->render->camera.x = -250;
	app->render->camera.y = -350;
	app->playerModule->SetPosition(900, 900);

	townScene = app->tex->Load("Assets/Art/Maps/town_map.png");
	NPCs = app->tex->Load("Assets/Art/NPCs/NPCs.png");
	return true;
}

// Called each loop iteration
bool TownScene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool TownScene::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y -= app->render->cameraSpeed;

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += app->render->cameraSpeed;


	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= app->render->cameraSpeed;


	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += app->render->cameraSpeed;

	SDL_Rect trianaSection = { 25,25, 75, 85 };
	SDL_Rect madonnaSection = {160,25, 60, 80};
	app->render->DrawTexture(townScene, 0, 0, NULL);
	app->render->DrawTexture(NPCs, 805, 320, &madonnaSection);
	app->render->DrawTexture(NPCs, 1185, 650, &trianaSection);



	return true;
}

// Called each loop iteration
bool TownScene::PostUpdate()
{
	bool ret = true;
	app->playerModule->GetPosition(playerPos.x, playerPos.y);
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		app->guiManager->pausePanel->Enable();
	if (playerPos.x < 0)app->fade->Fade(this, (Module*)app->tutorialForestScene);
	if (playerPos.y > 1000)app->fade->Fade(this, (Module*)app->startForestScene);

	return ret;
}

// Called before quitting
bool TownScene::CleanUp()
{
	LOG("Freeing scene");
	app->tex->UnLoad(townScene);
	app->tex->UnLoad(NPCs);
	return true;
}
