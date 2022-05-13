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

LogoScreen::LogoScreen(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer)
	: Scene(startEnabled, playerEnabled, name, cameraPos, playerPos, followPlayer)
{
	
}

// Destructor
LogoScreen::~LogoScreen()
{
	Scene::~Scene();
}

// Called before render is available
bool LogoScreen::Awake(pugi::xml_node& config)
{
	Scene::Awake(config);
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool LogoScreen::Start()
{
	Scene::Start();
	
	logoScreen = app->tex->Load("Assets/Art/GUI/logo.png");
	Logo_FX = app->audio->LoadFx("Assets/Audio/Fx/logo.wav");
	app->audio->PlayFx(Logo_FX);

	app->currentScene = sceneID::LOGO;
	return true;
}

// Called each loop iteration
bool LogoScreen::PreUpdate()
{
	Scene::PreUpdate();

	return true;
}

// Called each loop iteration
bool LogoScreen::Update(float dt)
{
	Scene::Update(dt);
	
	app->render->DrawTexture(logoScreen, 0, 0, NULL);

	if (count > 399) app->fade->Fade(this, (Module*)app->titleScreen);
	else count++;

	return true;
}

// Called each loop iteration
bool LogoScreen::PostUpdate()
{
	Scene::PostUpdate();
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) app->fade->Fade(this, (Module*)app->titleScreen);
		
	

	return ret;
}

// Called before quitting
bool LogoScreen::CleanUp()
{
	Scene::CleanUp();
	LOG("Freeing scene");
	app->tex->UnLoad(logoScreen);

	return true;
}
