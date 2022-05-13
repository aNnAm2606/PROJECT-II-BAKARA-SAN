#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeToBlack.h"
#include "TutorialScene_1.h"
#include "GuiManager.h"
#include "PlayerModule.h"
#include "Point.h"

#include "Defs.h"
#include "Log.h"

TutorialScene_1::TutorialScene_1(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer) :
	Scene(startEnabled, playerEnabled, name, cameraPos, playerPos, followPlayer)
{

}

// Destructor
TutorialScene_1::~TutorialScene_1()
{
	Scene::~Scene();
}

// Called before render is available
bool TutorialScene_1::Awake(pugi::xml_node& config)
{
	Scene::Awake(config);
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool TutorialScene_1::Start()
{
	Scene::Start();

	sceneTexture = app->tex->Load("Assets/Art/Maps/tutorial_map_1.png");

	app->audio->ChangeMusic(DUNGEON_MUSIC, 1.0f, 1.0f);

	app->currentScene = sceneID::TUTORIAL_4;
	return true;
}

// Called each loop iteration
bool TutorialScene_1::PreUpdate()
{
	Scene::PreUpdate();
	return true;
}

// Called each loop iteration
bool TutorialScene_1::Update(float dt)
{
	Scene::Update(dt);
	

	
	
	return true;
}

// Called each loop iteration
bool TutorialScene_1::PostUpdate()
{
	Scene::PostUpdate();
	bool ret = true;
	app->playerModule->GetPosition(playerPos.x, playerPos.y);

	if (playerPos.x > 1700) app->fade->Fade(this, (Module*)app->tutorialForestScene);


	return ret;
}

// Called before quitting
bool TutorialScene_1::CleanUp()
{
	Scene::CleanUp();
	LOG("Freeing scene");
	app->tex->UnLoad(sceneTexture);
	app->guiManager->pausePanel->Disable();

	return true;
}