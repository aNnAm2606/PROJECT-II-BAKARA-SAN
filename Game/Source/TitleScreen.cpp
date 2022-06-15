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

	app->render->camera.x = 0;
	app->render->camera.y = 0;

	startGame = false;
	anim = 0;
	ba = false;
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
	app->render->DrawTexture(bg, 0, 0, NULL,false);

	timer++; 
	if (timer >= 15)
	{
		if(ba == false)
			anim++;
		if(ba == true)
			anim--;

		timer = 0;
	}

	switch (anim)
	{
	case 0:
		app->render->DrawTexture(title, 54, 235, NULL, false);
		break;
	case 1:
		app->render->DrawTexture(title, 54, 240, NULL, false);
		break;
	case 2:
		app->render->DrawTexture(title, 54, 250, NULL, false);
		break;
	case 3:
		app->render->DrawTexture(title, 54, 255, NULL, false);
		break;
	case 4:
		app->render->DrawTexture(title, 54, 260, NULL, false);
		ba = !ba;
		break;
	}

	if (anim == 0) ba = !ba;
	return true;
}

// Called each loop iteration
bool TitleScreen::PostUpdate()
{
	app->render->DrawTexture(transparent, 0, 0, NULL, false);
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

	if (app->guiManager->back2Title == true)
	{
		app->transitions->SelectTransition(1, 0, 1280, this, (Module*)app->titleScreen);
		app->guiManager->back2Title = false;
	}
	return ret;
}

// Called before quitting
bool TitleScreen::CleanUp()
{
	Scene::CleanUp();
	LOG("Freeing scene");
	app->tex->UnLoad(bg);
	app->tex->UnLoad(title);
	app->tex->UnLoad(transparent);
	app->guiManager->titlePanel->Disable();
	app->guiManager->settingsPanel->Disable();
	app->guiManager->quitPanel->Disable();
	app->guiManager->creditsPanel->Disable();
	app->guiManager->pausePanel->Disable();
	return true;
}
