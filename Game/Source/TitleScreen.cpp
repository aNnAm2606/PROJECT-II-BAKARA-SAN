#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "TitleScreen.h"
#include "FadeToBlack.h"
#include "GuiManager.h"
#include "Transitions.h"
#include "easings.h"

#include "Defs.h"
#include "Log.h"

TitleScreen::TitleScreen(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer) :
	Scene(startEnabled, playerEnabled, name, cameraPos, playerPos, followPlayer)
{
	
}

// Destructor
TitleScreen::~TitleScreen()
{
	Scene::~Scene();
}

// Called before render is available
bool TitleScreen::Awake(pugi::xml_node& config)
{
	Scene::Awake(config);
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool TitleScreen::Start()
{
	Scene::Start();
	bg = app->tex->Load("Assets/Art/GUI/Background.png");
	title = app->tex->Load("Assets/Art/GUI/EXORQUEST.png");
	transparent = app->tex->Load("Assets/Art/GUI/transparent.png");
	app->guiManager->titlePanel->Enable();

	app->audio->ChangeMusic(TITLE_MUSIC, 0.0f, 0.0f);

	startGame = false;
	app->currentScene = sceneID::TITLE;
	return true;
}

// Called each loop iteration
bool TitleScreen::PreUpdate()
{
	Scene::PreUpdate();
	return true;
}

// Called each loop iteration
bool TitleScreen::Update(float dt)
{
	Scene::Update(dt);
	if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y -= 1;

	if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += 1;

	if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= 1;

	if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += 1;

	//if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	//{
	//	app->transitions->SelectTransition(1, 0, 1900);
	//}
	//if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	//{
	//	app->transitions->SelectTransition(2, 0, 1900);
	//}
	//if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	//{
	//	app->transitions->SelectTransition(3, 0, 1900);
	//}
	//if (app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
	//{
	//	app->transitions->SelectTransition(4, 0, 1900);
	//}

	app->render->DrawTexture(bg, 0, 0, NULL);


	//SDL_Rect Rect1;

	//Rect1.x = app->render->camera.x;
	//Rect1.y = app->render->camera.y;
	//Rect1.h = app->win->height;
	//Rect1.w = 0;
	//Rect1.w = EaseLinearIn(0 / 8, app->win->width / 64, app->win->width, 120);
	//Rect1.w = EaseLinearOut(300 / 8, app->win->width / 64, app->win->width, 60);
	SDL_Rect Rect1;
	Rect1.x = app->render->camera.x;
	Rect1.y = app->render->camera.y;
	Rect1.h = app->win->height / 5;
	Rect1.w = EaseLinearIn(0 / 8, app->win->width / 64, app->win->width, 60);
	app->render->DrawTexture(title, (Rect1.x + Rect1.w - 120), (Rect1.y - 10), NULL, 0, EaseLinearIn(0 / 24, app->win->width / 64, app->win->width, 240));
	//app->render->DrawTexture(title, 255, 255, NULL,0, EaseLinearIn(0 / 24, app->win->width / 64, app->win->width, 60));

	return true;
}

// Called each loop iteration
bool TitleScreen::PostUpdate()
{
	app->render->DrawTexture(transparent, 0, 0, NULL);
	Scene::PostUpdate();
	bool ret = true;

	if (startGame == true)
	{
		if (continueGame == true)
		{
			app->LoadGameRequest();
		}
		else
		{
			app->transitions->SelectTransition(1, 0,1280, this, (Module*)app->tutorialScene_1);
		}
	}

	if(app->guiManager->settingsPanel->GetActive() == false
		&& app->guiManager->quitPanel->GetActive() == false
		&& app->guiManager->creditsPanel->GetActive() == false
		&& app->guiManager->pausePanel->GetActive() == false)
		app->guiManager->titlePanel->Enable();
	else
		app->guiManager->titlePanel->Disable();

	return ret;
}

// Called before quitting
bool TitleScreen::CleanUp()
{
	Scene::CleanUp();
	LOG("Freeing scene");
	app->tex->UnLoad(bg);
	app->guiManager->titlePanel->Disable();
	app->guiManager->settingsPanel->Disable();
	app->guiManager->quitPanel->Disable();
	app->guiManager->creditsPanel->Disable();
	app->guiManager->pausePanel->Disable();
	return true;
}
