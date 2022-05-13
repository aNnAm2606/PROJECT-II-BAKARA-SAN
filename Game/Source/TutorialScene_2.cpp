#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeToBlack.h"
#include "TutorialScene_2.h"
#include "GuiManager.h"
#include "PlayerModule.h"
#include "Point.h"

#include "Defs.h"
#include "Log.h"

TutorialScene_2::TutorialScene_2(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer) :
	Scene(startEnabled, playerEnabled, name, cameraPos, playerPos, followPlayer)
{

}

// Destructor
TutorialScene_2::~TutorialScene_2()
{
	Scene::~Scene();
}

// Called before render is available
bool TutorialScene_2::Awake(pugi::xml_node& config)
{
	Scene::Awake(config);
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool TutorialScene_2::Start()
{
	Scene::Start();

	sceneTexture = app->tex->Load("Assets/Art/Maps/tutorial_map_2.png");

	app->audio->ChangeMusic(DUNGEON_MUSIC, 1.0f, 1.0f);

	app->currentScene = sceneID::TUTORIAL_4;
	return true;
}

// Called each loop iteration
bool TutorialScene_2::PreUpdate()
{
	Scene::PreUpdate();
	return true;
}

// Called each loop iteration
bool TutorialScene_2::Update(float dt)
{
	Scene::Update(dt);




	return true;
}

// Called each loop iteration
bool TutorialScene_2::PostUpdate()
{
	Scene::PostUpdate();
	bool ret = true;
	app->playerModule->GetPosition(playerPos.x, playerPos.y);

	if (playerPos.x > 1700) app->fade->Fade(this, (Module*)app->tutorialForestScene);


	return ret;
}

// Called before quitting
bool TutorialScene_2::CleanUp()
{
	Scene::CleanUp();
	LOG("Freeing scene");
	app->tex->UnLoad(sceneTexture);
	app->guiManager->pausePanel->Disable();

	return true;
}