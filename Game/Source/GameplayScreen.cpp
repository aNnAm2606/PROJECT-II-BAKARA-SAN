#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "GameplaySceen.h"
#include "FadeToBlack.h"
#include "GuiManager.h"

#include "Defs.h"
#include "Log.h"

GameplayScreen::GameplayScreen(bool startEnabled) : Module(startEnabled)
{
	name.Create("GameplayScreen");
}

// Destructor
GameplayScreen::~GameplayScreen()
{}

// Called before render is available
bool GameplayScreen::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool GameplayScreen::Start()
{
	//app->audio->PlayMusic("Assets/Audio/Music/world_map.ogg")
	bg = app->tex->Load("Assets/Art/Maps/tutorial_map_part1.png");
	return true;
}

// Called each loop iteration
bool GameplayScreen::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool GameplayScreen::Update(float dt)
{
	if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y += 1;

	if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y -= 1;

	if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x += 1;

	if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x -= 1;

	app->render->DrawTexture(bg, 0, 0, NULL);

	return true;
}

// Called each loop iteration
bool GameplayScreen::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		app->guiManager->pausePanel->Enable();

	return ret;
}

// Called before quitting
bool GameplayScreen::CleanUp()
{
	LOG("Freeing scene");
	app->tex->UnLoad(bg);
	app->guiManager->settingsPanel->Disable();
	app->guiManager->pausePanel->Disable();
	return true;
}
