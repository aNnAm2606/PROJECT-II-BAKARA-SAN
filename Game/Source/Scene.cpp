#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeToBlack.h"
#include "Scene.h"
#include "GuiManager.h"
#include "PlayerModule.h"
#include "Point.h"
#include "Transitions.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene(bool startEnabled, bool playerEnabled,SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer) : Module(startEnabled)
{
	isPlayerEnabled = playerEnabled;
	name.Create(sceneName.GetString());
	startCameraPos = cameraPos;
	startPlayerPos = playerPos;
	startCameraFollowsPlayer = followPlayer;
	
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	app->render->camera.x = startCameraPos.x;
	app->render->camera.y = startCameraPos.y;
	if (isPlayerEnabled)
	{
		app->playerModule->Enable();
		app->playerModule->SetPosition(startPlayerPos.x, startPlayerPos.y);

		cameraFollowsPlayer = startCameraFollowsPlayer;

		app->render->followPlayerX = cameraFollowsPlayer.x;
		app->render->followPlayerY = cameraFollowsPlayer.y;
	}
	else app->playerModule->Disable();
	

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	GamePad& gamepad = app->input->pads[0];
	
	if(sceneTexture != NULL) app->render->DrawTexture(sceneTexture, 0, 0, NULL);
	
	

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;
	if (isPlayerEnabled)
	{
		if (cameraFollowsPlayer.x)app->render->followPlayerX = true;
		else app->render->followPlayerX = false;

		if (cameraFollowsPlayer.y)app->render->followPlayerY = true;
		else app->render->followPlayerY = false;
	}
	
	if (app->guiManager->back2Title == true)
	{
		app->transitions->SelectTransition(1, 0, 1280, this, (Module*)app->titleScreen);
		app->guiManager->back2Title = false;
	}


	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");
	colliderList.Clear();
	app->tex->UnLoad(sceneTexture);
	app->guiManager->pausePanel->Disable();

	return true;
}

