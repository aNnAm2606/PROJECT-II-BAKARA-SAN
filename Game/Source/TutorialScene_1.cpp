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
#include "Transitions.h"

#include "QuestModule.h"

#include "Defs.h"
#include "Log.h"

TutorialScene_1::TutorialScene_1(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer) :
	Scene(startEnabled, playerEnabled, name, cameraPos, playerPos, followPlayer)
{
	mapCol01 = new Collider({ 1360,0,100,400 }, Collider::WALL);
	mapCol02 = new Collider({ 0,300,1900,20 }, Collider::WALL);
	mapCol03 = new Collider({ 0,900,1900,20 }, Collider::WALL);
	mapCol04 = new Collider({ 0,480,1900,20 }, Collider::WALL);
	mapCol05 = new Collider({ 0,0,1900,20 }, Collider::WALL);
	

	colliderList.Add(mapCol01);
	colliderList.Add(mapCol02);
	colliderList.Add(mapCol03);
	colliderList.Add(mapCol04);
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
	Fade_FX = app->audio->LoadFx("Assets/Audio/Fx/fade_in.wav");

	app->audio->ChangeMusic(DUNGEON1_MUSIC, 1.0f, 1.0f);
	app->audio->PlayFx(Fade_FX);

	app->currentScene = sceneID::TUTORIAL_1;

	app->quests->ActivateQuest(QuestModule::EQuest::EQUEST_PM_Q2);

	m_Gargoyle_1.Init();
	m_Gargoyle_1.SetPosition(913, 150);
	m_Gargoyle_1.SetOriginScene(this);

	m_Gargoyle_2.Init();
	m_Gargoyle_2.SetPosition(925, 720);
	m_Gargoyle_2.SetOriginScene(this);

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

	m_Gargoyle_1.Update();
	m_Gargoyle_2.Update();

	SDL_Rect playerRect = app->playerModule->GetPLayerCollider()->rect;

	if (mapCol01->Intersects(playerRect))
	{
		app->playerModule->SetPosition(playerPos.x -20, playerPos.y);
	}
	if (mapCol02->Intersects(playerRect))
	{
		app->playerModule->SetPosition(playerPos.x, playerPos.y -20);
	}
	if (mapCol03->Intersects(playerRect))
	{
		app->playerModule->SetPosition(playerPos.x, playerPos.y -20);
	}
	if (mapCol04->Intersects(playerRect))
	{
		app->playerModule->SetPosition(playerPos.x, playerPos.y +20);
	}
	if (mapCol05->Intersects(playerRect))
	{
		app->playerModule->SetPosition(playerPos.x, playerPos.y + 20);
	}
	return true;
}

// Called each loop iteration
bool TutorialScene_1::PostUpdate()
{
	Scene::PostUpdate();
	bool ret = true;
	app->playerModule->GetPosition(playerPos.x, playerPos.y);

	//if (playerPos.x < 1000) app->fade->Fade(this, (Module*)app->tutorialForestScene);
	if (playerPos.x < 600 && playerPos.y < 400)
	{
		app->playerModule->SetPosition(1450, 720);
		app->render->camera.y = -350;
	}
	if (playerPos.x > 1550 && playerPos.y > 400)
	{
		app->playerModule->SetPosition(700, 150);
		app->render->camera.y = 0;
	}
	if (playerPos.x < 600 && playerPos.y > 400)
	{
		startPlayerPos = { 650, 700 };
		startCameraPos = { app->render->camera.x, app->render->camera.y };
		startCameraFollowsPlayer = cameraFollowsPlayer;
		app->transitions->SelectTransition(1, 0, 1280, this, (Module*)app->tutorialScene_2);
	}
	if (app->guiManager->back2Title == true)
	{
		app->transitions->SelectTransition(1, 0, 1280, this, (Module*)app->titleScreen);
	}

	m_Gargoyle_1.Render();
	m_Gargoyle_2.Render();

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

bool TutorialScene_1::SaveState(pugi::xml_node& save)
{
	save.append_child("gargoyle_1").text() = m_Gargoyle_1.IsActive();
	save.append_child("gargoyle_2").text() = m_Gargoyle_2.IsActive();

	return true;
}

bool TutorialScene_1::LoadState(pugi::xml_node& load)
{
	m_Gargoyle_1.SetActive(load.child("gargoyle_1").text().as_bool());
	m_Gargoyle_2.SetActive(load.child("gargoyle_2").text().as_bool());

	return true;
}