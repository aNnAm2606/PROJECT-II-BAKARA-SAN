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
#include "Transitions.h"

#include "Defs.h"
#include "Log.h"

TutorialScene_2::TutorialScene_2(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer) :
	Scene(startEnabled, playerEnabled, name, cameraPos, playerPos, followPlayer)
{
	mapCol01 = new Collider({ 0,0,1900,260 }, Collider::WALL);
	mapCol02 = new Collider({ 0,700,1900,260 }, Collider::WALL);

	colliderList.Add(mapCol01);
	colliderList.Add(mapCol02);

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
	Fade_FX = app->audio->LoadFx("Assets/Audio/Fx/fade_in.wav");
	app->audio->PlayFx(Fade_FX);
	sceneTexture = app->tex->Load("Assets/Art/Maps/tutorial_map_2.png");

	app->currentScene = sceneID::TUTORIAL_2;

	m_Gargoyle.Init();
	m_Gargoyle.SetPosition(966, 450);
	m_Gargoyle.SetOriginScene(this);

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

	m_Gargoyle.Update();

	SDL_Rect playerRect = app->playerModule->GetPLayerCollider()->rect;

	if (mapCol01->Intersects(playerRect))
	{
		app->playerModule->SetPosition(playerPos.x, playerPos.y +20);
	}
	if (mapCol02->Intersects(playerRect))
	{
		app->playerModule->SetPosition(playerPos.x, playerPos.y - 20);
	}

	return true;
}

// Called each loop iteration
bool TutorialScene_2::PostUpdate()
{
	Scene::PostUpdate();
	bool ret = true;
	app->playerModule->GetPosition(playerPos.x, playerPos.y);

	if (playerPos.x > 1500)
	{
		startPlayerPos = { 1400, 450 };
		startCameraPos = { app->render->camera.x, app->render->camera.y };
		startCameraFollowsPlayer = cameraFollowsPlayer;
		app->transitions->SelectTransition(1, 0, 1280, this, (Module*)app->tutorialScene_1);
	}
	if (playerPos.x < 500)
	{
		startPlayerPos = { 650, 450 };
		startCameraPos = { app->render->camera.x, app->render->camera.y };
		startCameraFollowsPlayer = cameraFollowsPlayer;
		app->transitions->SelectTransition(1, 0, 1280, this, (Module*)app->tutorialScene_3);
	}

	if (app->guiManager->back2Title == true)
	{
		app->transitions->SelectTransition(1, 0, 1280, this, (Module*)app->titleScreen);
	}

	m_Gargoyle.Render();

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

bool TutorialScene_2::SaveState(pugi::xml_node& save)
{
	save.append_child("gargoyle").text() = m_Gargoyle.IsActive();

	return true;
}

bool TutorialScene_2::LoadState(pugi::xml_node& load)
{
	m_Gargoyle.SetActive(load.child("gargoyle").text().as_bool());

	return true;
}