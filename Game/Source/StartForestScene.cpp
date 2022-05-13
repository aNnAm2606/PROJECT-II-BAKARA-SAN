#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeToBlack.h"
#include "StartForestScene.h"
#include "GuiManager.h"
#include "PlayerModule.h"
#include "Point.h"

#include "Defs.h"
#include "Log.h"

StartForestScene::StartForestScene(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer) : 
	Scene( startEnabled,  playerEnabled,  name,  cameraPos, playerPos, followPlayer)
{
	
}

// Destructor
StartForestScene::~StartForestScene()
{
	Scene::~Scene();
}

// Called before render is available
bool StartForestScene::Awake(pugi::xml_node& config)
{
	Scene::Awake(config);
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool StartForestScene::Start()
{
	Scene::Start();
	
	sceneTexture = app->tex->Load("Assets/Art/Maps/start_forest_map.png");
	app->audio->ChangeMusic(SANCTUARY_MUSIC, 1.0f, 1.0f);

	app->currentScene = sceneID::START_FOREST;
	
	return true;
}

// Called each loop iteration
bool StartForestScene::PreUpdate()
{
	Scene::PreUpdate();
	return true;
}

// Called each loop iteration
bool StartForestScene::Update(float dt)
{
	Scene::Update( dt);
	
	app->playerModule->GetPosition(playerPos.x, playerPos.y);

	if (playerPos.x < 700 || playerPos.x > 1250) cameraFollowsPlayer.x = false;
	else cameraFollowsPlayer.x = true;

	if (playerPos.y < 375 || playerPos.y > 700) cameraFollowsPlayer.y = false;
	else cameraFollowsPlayer.y = true;

	return true;
}

// Called each loop iteration
bool StartForestScene::PostUpdate()
{
	Scene::PostUpdate();
	bool ret = true;

	if (playerPos.y < -200)
	{
		startPlayerPos = { playerPos.x, 30 };
		startCameraPos = { app->render->camera.x, app->render->camera.y };
		startCameraFollowsPlayer = cameraFollowsPlayer;
		app->fade->Fade(this, (Module*)app->townScene);
	}
	 

	return ret;
}

// Called before quitting
bool StartForestScene::CleanUp()
{
	Scene::CleanUp();
	LOG("Freeing scene");
	
	return true;
}