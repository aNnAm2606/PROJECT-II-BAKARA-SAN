#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeToBlack.h"
#include "TownScene.h"

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
	app->render->camera.x = 0;
	app->render->camera.y = 0;

	townScene = app->tex->Load("Assets/Art/Maps/town_map.png");
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
		app->render->camera.y -= 1;

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += 1;

	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= 1;

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += 1;

	

	return true;
}

// Called each loop iteration
bool TownScene::PostUpdate()
{
	bool ret = true;

	app->render->DrawTexture(townScene, 0, 0, NULL);

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) app->fade->Fade(this, (Module*)app->tutorialForestScene);

	return ret;
}

// Called before quitting
bool TownScene::CleanUp()
{
	LOG("Freeing scene");
	app->tex->UnLoad(townScene);
	return true;
}
