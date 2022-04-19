#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "TitleScreen.h"
#include "FadeToBlack.h"
#include "GuiManager.h"

#include "Defs.h"
#include "Log.h"

TitleScreen::TitleScreen() : Module()
{
	name.Create("TitleScreen");
}

// Destructor
TitleScreen::~TitleScreen()
{}

// Called before render is available
bool TitleScreen::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool TitleScreen::Start()
{
	//app->audio->PlayMusic("Assets/Audio/Music/world_map.ogg");
	bg = app->tex->Load("Assets/Art/GUI/TitlescreenBg.png");
	app->guiManager->titlePanel->Enable();

	startGame = false;
	return true;
}

// Called each loop iteration
bool TitleScreen::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool TitleScreen::Update(float dt)
{
	if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y -= 1;

	if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += 1;

	if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= 1;

	if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += 1;

	app->render->DrawTexture(bg, 0, 0, NULL);

	return true;
}

// Called each loop iteration
bool TitleScreen::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	if (startGame == true) 
		app->fade->Fade(this, (Module*)app->logoScreen);

	if(app->guiManager->settingsPanel->GetActive() == false && app->guiManager->quitPanel->GetActive() == false && app->guiManager->creditsPanel->GetActive() == false)
		app->guiManager->titlePanel->Enable();
	else
		app->guiManager->titlePanel->Disable();

	return ret;
}

// Called before quitting
bool TitleScreen::CleanUp()
{
	LOG("Freeing scene");
	app->tex->UnLoad(bg);
	app->guiManager->titlePanel->Disable();
	app->guiManager->settingsPanel->Disable();
	app->guiManager->quitPanel->Disable();
	return true;
}
