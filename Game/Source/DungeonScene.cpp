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

	
	background1 = app->tex->Load("Assets/Art/Maps/dungeon_map_1.png");
	background2 = app->tex->Load("Assets/Art/Maps/dungeon_map_2.png");
	background3 = app->tex->Load("Assets/Art/Maps/dungeon_map_3.png");
	background4 = app->tex->Load("Assets/Art/Maps/dungeon_map_4.png");

	app->audio->ChangeMusic(DUNGEON_MUSIC, 1.0f, 1.0f);

	app->currentScene = sceneID::DUNGEON;
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

	if (playerPos.x < 700 || playerPos.x > 1250) cameraFollowsPlayer.x = false;
	else cameraFollowsPlayer.x = true;

	if (playerPos.y < -2850 || playerPos.y > 700) cameraFollowsPlayer.y = false;
	else cameraFollowsPlayer.y = true;


	app->render->DrawTexture(background4, 0, 0, NULL);
	app->render->DrawTexture(background3, 0, -1080, NULL);
	app->render->DrawTexture(background2, 0, -2160, NULL);
	app->render->DrawTexture(background1, 0, -3240, NULL);


	return true;
}

// Called each loop iteration
bool DungeonScene::PostUpdate()
{
	Scene::PostUpdate();
	bool ret = true;
	app->playerModule->GetPosition(playerPos.x, playerPos.y);

	if (playerPos.y > 800) app->fade->Fade(this, (Module*)app->worldMapScene);


	return ret;
}

// Called before quitting
bool DungeonScene::CleanUp()
{
	Scene::CleanUp();
	LOG("Freeing scene");

	app->tex->UnLoad(background4);
	app->tex->UnLoad(background3);
	app->tex->UnLoad(background2);
	app->tex->UnLoad(background1);

	app->guiManager->pausePanel->Disable();

	return true;
}