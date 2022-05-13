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
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y -= app->render->cameraSpeed;

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += app->render->cameraSpeed;


	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= app->render->cameraSpeed;


	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += app->render->cameraSpeed;
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
	
	


	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");
	app->tex->UnLoad(sceneTexture);
	app->guiManager->pausePanel->Disable();

	return true;
}

