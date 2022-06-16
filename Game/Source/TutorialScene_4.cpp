#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeToBlack.h"
#include "TutorialScene_4.h"
#include "GuiManager.h"
#include "PlayerModule.h"
#include "Point.h"
#include "Transitions.h"

#include "Defs.h"
#include "Log.h"

TutorialScene_4::TutorialScene_4(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer) :
	Scene(startEnabled, playerEnabled, name, cameraPos, playerPos, followPlayer)
{
	mapCol01 = new Collider({ 0,0,1900,150 }, Collider::WALL);
	mapCol02 = new Collider({ 0,880, 1900, 30 }, Collider::WALL);

	colliderList.Add(mapCol01);
	colliderList.Add(mapCol02);
}

// Destructor
TutorialScene_4::~TutorialScene_4()
{
	Scene::~Scene();
}

// Called before render is available
bool TutorialScene_4::Awake(pugi::xml_node& config)
{
	Scene::Awake(config);
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool TutorialScene_4::Start()
{
	Scene::Start();
	
	sceneTexture = app->tex->Load("Assets/Art/Maps/tutorial_map_4.png");

	Fade_FX = app->audio->LoadFx("Assets/Audio/Fx/fade_in.wav");
	app->audio->PlayFx(Fade_FX);
	app->audio->ChangeMusic(DUNGEON2_MUSIC, 1.0f, 1.0f);

	
	m_Gargoyle.Init();

	app->currentScene = sceneID::TUTORIAL_4;
	return true;
}

// Called each loop iteration
bool TutorialScene_4::PreUpdate()
{
	Scene::PreUpdate();
	return true;
}

// Called each loop iteration
bool TutorialScene_4::Update(float dt)
{
	Scene::Update(dt);
	m_Gargoyle.Update();

	m_Gargoyle.Render();

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
bool TutorialScene_4::PostUpdate()
{
	Scene::PostUpdate();
	bool ret = true;
	app->playerModule->GetPosition(playerPos.x, playerPos.y);

	if (playerPos.x > 1500)
	{
		startPlayerPos = { 1400, 450 };
		startCameraPos = { app->render->camera.x, app->render->camera.y };
		startCameraFollowsPlayer = cameraFollowsPlayer;
		app->transitions->SelectTransition(1, 0, 1280, this, (Module*)app->tutorialScene_3);
	}
	if (playerPos.x < 500)
	{
		startPlayerPos = { 650, 450 };
		startCameraPos = { app->render->camera.x, app->render->camera.y };
		startCameraFollowsPlayer = cameraFollowsPlayer;
		app->transitions->SelectTransition(1, 0, 1280, this, (Module*)app->tutorialForestScene);
	}
	if (app->guiManager->back2Title == true)
	{
		app->transitions->SelectTransition(1, 0, 1280, this, (Module*)app->titleScreen);
	}

	return ret;
}

// Called before quitting
bool TutorialScene_4::CleanUp()
{
	Scene::CleanUp();
	LOG("Freeing scene");
	app->guiManager->pausePanel->Disable();

	return true;
}

bool TutorialScene_4::SaveState(pugi::xml_node& save)
{
	save.append_child("gargoyle").text() = m_Gargoyle.IsActive();

	return true;
}

bool TutorialScene_4::LoadState(pugi::xml_node& load)
{
	m_Gargoyle.SetActive(load.child("gargoyle").text().as_bool());

	return true;
}