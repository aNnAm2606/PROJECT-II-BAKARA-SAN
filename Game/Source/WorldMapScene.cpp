#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeToBlack.h"
#include "WorldMapScene.h"
#include "GuiManager.h"
#include "PlayerModule.h"
#include "Point.h"
#include "Transitions.h"

#include "Defs.h"
#include "Log.h"

WorldMapScene::WorldMapScene(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer) :
	Scene(startEnabled, playerEnabled, name, cameraPos, playerPos, followPlayer)
{

}

// Destructor
WorldMapScene::~WorldMapScene()
{
	Scene::~Scene();
}

// Called before render is available
bool WorldMapScene::Awake(pugi::xml_node& config)
{
	Scene::Awake(config);
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool WorldMapScene::Start()
{
	Scene::Start();

	sceneTexture = app->tex->Load("Assets/Art/Maps/world_map.png");

	app->audio->ChangeMusic(DUNGEON_MUSIC, 1.0f, 1.0f);

	app->currentScene = sceneID::WORLD_MAP;
	return true;
}

// Called each loop iteration
bool WorldMapScene::PreUpdate()
{
	Scene::PreUpdate();
	return true;
}

// Called each loop iteration
bool WorldMapScene::Update(float dt)
{
	Scene::Update(dt);




	return true;
}

// Called each loop iteration
bool WorldMapScene::PostUpdate()
{
	Scene::PostUpdate();
	bool ret = true;
	if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)		app->transitions->SelectTransition(1, 0, 1280, this, (Module*)app->startForestScene);
	if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)		app->transitions->SelectTransition(1, 0, 1280, this, (Module*)app->townScene);
	if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)		app->transitions->SelectTransition(1, 0, 1280, this, (Module*)app->dungeonScene);


	return ret;
}

// Called before quitting
bool WorldMapScene::CleanUp()
{
	Scene::CleanUp();
	LOG("Freeing scene");
	app->tex->UnLoad(sceneTexture);
	app->guiManager->pausePanel->Disable();

	return true;
}