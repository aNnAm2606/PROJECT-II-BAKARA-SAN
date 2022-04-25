#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeToBlack.h"
#include "TutorialForestScene.h"
#include "GuiManager.h"
#include "PlayerModule.h"
#include "Point.h"

#include "Defs.h"
#include "Log.h"

TutorialForestScene::TutorialForestScene(bool startEnabled) : Module(startEnabled)
{
	name.Create("StartForestScene");
}

// Destructor
TutorialForestScene::~TutorialForestScene()
{}

// Called before render is available
bool TutorialForestScene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool TutorialForestScene::Start()
{
	app->render->camera.x = -600;
	app->render->camera.y = -150;
	app->playerModule->SetPosition(1700, 600);
	tutorialForestScene = app->tex->Load("Assets/Art/Maps/out_of_tutorial_map.png");

	app->render->followPlayerX = false;
	app->render->followPlayerY = false;

	m_AlanParsons.Init();

	return true;
}

// Called each loop iteration
bool TutorialForestScene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool TutorialForestScene::Update(float dt)
{
	m_AlanParsons.Update();

	app->render->DrawTexture(tutorialForestScene, 0, 0, NULL);
	m_AlanParsons.Render();

	app->playerModule->GetPosition(playerPos.x, playerPos.y);
	if (playerPos.x < 650 || playerPos.x > 1250) app->render->followPlayerX = false;
	else app->render->followPlayerX = true;

	
	
	return true;
}

// Called each loop iteration
bool TutorialForestScene::PostUpdate()
{
	bool ret = true;
	app->playerModule->GetPosition(playerPos.x, playerPos.y);
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		app->guiManager->pausePanel->Enable();
	if (playerPos.x > 1800)app->fade->Fade(this, (Module*)app->townScene);
	if (playerPos.x < 100) app->fade->Fade(this, (Module*)app->tutorialScene_4);

	return ret;
}

// Called before quitting
bool TutorialForestScene::CleanUp()
{
	LOG("Freeing scene");
	app->tex->UnLoad(tutorialForestScene);
	return true;
}
