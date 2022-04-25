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
	app->render->camera.x = -150;
	app->render->camera.y = -360;
	app->playerModule->SetPosition(900, 800);

	townScene = app->tex->Load("Assets/Art/Maps/town_map.png");
	NPCs = app->tex->Load("Assets/Art/NPCs/NPCs.png");

	app->render->followPlayerX = true;
	app->render->followPlayerY = false;
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


	app->playerModule->GetPosition(playerPos.x, playerPos.y);
	if (playerPos.x < 650 || playerPos.x > 1275) app->render->followPlayerX = false;
	else app->render->followPlayerX = true;

	if (playerPos.y < 375 || playerPos.y > 710) app->render->followPlayerY = false;
	else app->render->followPlayerY = true;



	return true;
}

// Called each loop iteration
bool TownScene::PostUpdate()
{
	bool ret = true;
	
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
