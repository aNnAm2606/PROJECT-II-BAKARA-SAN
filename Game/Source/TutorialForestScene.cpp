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
#include "Transitions.h"

#include "Defs.h"
#include "Log.h"

TutorialForestScene::TutorialForestScene(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer) :
	Scene(startEnabled, playerEnabled, name, cameraPos, playerPos, followPlayer)
{
	mapCol01 = new Collider({ 400, 0, 1900, 550 }, Collider::WALL);
	mapCol02 = new Collider({ 0, 700, 1900, 50 }, Collider::WALL);

	colliderList.Add(mapCol01);
	colliderList.Add(mapCol02);
}

// Destructor
TutorialForestScene::~TutorialForestScene()
{
	Scene::~Scene();
}

// Called before render is available
bool TutorialForestScene::Awake(pugi::xml_node& config)
{
	Scene::Awake(config);
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool TutorialForestScene::Start()
{
	Scene::Start();
	
	sceneTexture = app->tex->Load("Assets/Art/Maps/tutorial_forest_map.png");

	Fade_FX = app->audio->LoadFx("Assets/Audio/Fx/fade_in.wav");
	app->audio->PlayFx(Fade_FX);
	app->audio->ChangeMusic(FOREST_MUSIC, 1.0f, 1.0f);

	m_AlanParsons.Init();

	app->currentScene = sceneID::TUTORIAL_FOREST;
	return true;
}

// Called each loop iteration
bool TutorialForestScene::PreUpdate()
{
	Scene::PreUpdate();
	return true;
}

// Called each loop iteration
bool TutorialForestScene::Update(float dt)
{
	Scene::Update(dt);
	m_AlanParsons.Update();

	m_AlanParsons.Render();

	app->playerModule->GetPosition(playerPos.x, playerPos.y);

	if (playerPos.x < 650 || playerPos.x > 1250) cameraFollowsPlayer.x = false;
	else cameraFollowsPlayer.x = true;

	SDL_Rect playerRect = app->playerModule->GetPLayerCollider()->rect;

	if (mapCol01->Intersects(playerRect))
	{
		app->playerModule->SetPosition(playerPos.x, playerPos.y + 20);
	}
	if (mapCol02->Intersects(playerRect))
	{
		app->playerModule->SetPosition(playerPos.x, playerPos.y - 20);
	}
	
	return true;
}

// Called each loop iteration
bool TutorialForestScene::PostUpdate()
{
	Scene::PostUpdate();
	bool ret = true;

	app->playerModule->GetPosition(playerPos.x, playerPos.y);

	if (playerPos.x > 1800)
	{
		startPlayerPos = { 1500, 600 };
		startCameraPos = { app->render->camera.x, app->render->camera.y };
		startCameraFollowsPlayer = cameraFollowsPlayer;
		app->transitions->SelectTransition(1, 0, 1280, this, (Module*)app->startForestScene);
		
	}
	if (playerPos.x < 100)
	{
		startPlayerPos = { 250, 600 };
		startCameraPos = { app->render->camera.x, app->render->camera.y };
		startCameraFollowsPlayer = cameraFollowsPlayer;
		app->transitions->SelectTransition(1, 0, 1280, this, (Module*)app->tutorialScene_4);
	}

	if (app->guiManager->back2Title == true)
	{
		app->transitions->SelectTransition(1, 0, 1280, this, (Module*)app->titleScreen);
	}
	return ret;
}

// Called before quitting
bool TutorialForestScene::CleanUp()
{
	Scene::CleanUp();
	LOG("Freeing scene");
	
	return true;
}
