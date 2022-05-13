#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeToBlack.h"
#include "DungeonScene.h"
#include "GuiManager.h"
#include "PlayerModule.h"
#include "Point.h"

#include "Defs.h"
#include "Log.h"

DungeonScene::DungeonScene(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer) :
	Scene(startEnabled, playerEnabled, name, cameraPos, playerPos, followPlayer)
{

}

// Destructor
DungeonScene::~DungeonScene()
{
	Scene::~Scene();
}

// Called before render is available
bool DungeonScene::Awake(pugi::xml_node& config)
{
	Scene::Awake(config);
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool DungeonScene::Start()
{
	Scene::Start();

	
	Background1 = app->tex->Load("Assets/Art/Maps/dungeon_map_1.png");
	Background2 = app->tex->Load("Assets/Art/Maps/dungeon_map_2.png");
	Background3 = app->tex->Load("Assets/Art/Maps/dungeon_map_3.png");
	Background4 = app->tex->Load("Assets/Art/Maps/dungeon_map_4.png");

	app->audio->ChangeMusic(DUNGEON_MUSIC, 1.0f, 1.0f);

	app->currentScene = sceneID::TUTORIAL_4;
	return true;
}

// Called each loop iteration
bool DungeonScene::PreUpdate()
{
	Scene::PreUpdate();
	return true;
}

// Called each loop iteration
bool DungeonScene::Update(float dt)
{
	Scene::Update(dt);




	return true;
}

// Called each loop iteration
bool DungeonScene::PostUpdate()
{
	Scene::PostUpdate();
	bool ret = true;
	app->playerModule->GetPosition(playerPos.x, playerPos.y);

	if (playerPos.x > 1700) app->fade->Fade(this, (Module*)app->tutorialForestScene);


	return ret;
}

// Called before quitting
bool DungeonScene::CleanUp()
{
	Scene::CleanUp();
	LOG("Freeing scene");

	app->tex->UnLoad(Background4);
	app->tex->UnLoad(Background3);
	app->tex->UnLoad(Background2);
	app->tex->UnLoad(Background1);

	app->guiManager->pausePanel->Disable();

	return true;
}