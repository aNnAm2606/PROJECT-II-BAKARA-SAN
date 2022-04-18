#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "LogoScreen.h"
#include "FadeToBlack.h"

#include "Defs.h"
#include "Log.h"

LogoScreen::LogoScreen() : Module()
{
	name.Create("LogoScreen");
}

// Destructor
LogoScreen::~LogoScreen()
{}

// Called before render is available
bool LogoScreen::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool LogoScreen::Start()
{
	/*img = app->tex->Load("Assets/Textures/test.png");
	app->audio->PlayMusic("Assets/Audio/Music/music_spy.ogg");*/
	logoScreen = app->tex->Load("Assets/Art/GUI/logo.png");
	return true;
}

// Called each loop iteration
bool LogoScreen::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool LogoScreen::Update(float dt)
{
	if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y -= 1;

	if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += 1;

	if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= 1;

	if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += 1;

	//app->render->DrawTexture(img, 380, 100);

	return true;
}

// Called each loop iteration
bool LogoScreen::PostUpdate()
{
	bool ret = true;

	app->render->DrawTexture(logoScreen, 0, 0, NULL);

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) app->fade->Fade(this, (Module*)app->titleScreen);

	return ret;
}

// Called before quitting
bool LogoScreen::CleanUp()
{
	LOG("Freeing scene");
	app->tex->UnLoad(logoScreen);
	return true;
}
