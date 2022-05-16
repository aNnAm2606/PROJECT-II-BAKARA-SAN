#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeToBlack.h"
#include "TownScene.h"
#include "GuiManager.h"
#include "PlayerModule.h"

#include "Defs.h"
#include "Log.h"

TownScene::TownScene(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer) :
	Scene(startEnabled, playerEnabled, name, cameraPos, playerPos, followPlayer)
{
	
}

// Destructor
TownScene::~TownScene()
{
	Scene::~Scene();

}

// Called before render is available
bool TownScene::Awake(pugi::xml_node& config)
{
	Scene::Awake(config);
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool TownScene::Start()
{
	Scene::Start();

	sceneTexture = app->tex->Load("Assets/Art/Maps/town_map.png");
	Fade_FX = app->audio->LoadFx("Assets/Audio/Fx/fade_in.wav");
	app->audio->ChangeMusic(TOWN_MUSIC, 1.0f, 1.0f);

	m_Triana.Init();
	m_SisterMadonna.Init();
	m_StevenWonder.Init();
	m_DavidBow.Init();
	m_Cat.Init();
	m_GargoyleTest.Init();
	m_GargoyleTest.SetPosition(1560, 650);
	m_GargoyleTest.SetOriginScene(this);

	app->currentScene = sceneID::TOWN;

	return true;
}

// Called each loop iteration
bool TownScene::PreUpdate()
{
	Scene::PreUpdate();
	return true;
}

// Called each loop iteration
bool TownScene::Update(float dt)
{
	Scene::Update(dt);
	m_Triana.Update();
	m_SisterMadonna.Update();
	m_StevenWonder.Update();
	m_DavidBow.Update();
	m_Cat.Update();
	m_GargoyleTest.Update();

	m_SisterMadonna.Render();
	m_Triana.Render();
	m_StevenWonder.Render();
	m_DavidBow.Render();
	m_Cat.Render();
	m_GargoyleTest.Render();



	app->playerModule->GetPosition(playerPos.x, playerPos.y);
	if (playerPos.x < 650 || playerPos.x > 1275) cameraFollowsPlayer.x = false;
	else cameraFollowsPlayer.x = true;

	if (playerPos.y < 375 || playerPos.y > 710) cameraFollowsPlayer.y = false;
	else cameraFollowsPlayer.y = true;



	return true;
}

// Called each loop iteration
bool TownScene::PostUpdate()
{
	Scene::PostUpdate();
	bool ret = true;
	
	if (playerPos.y > 1000)app->fade->Fade(this, (Module*) app->worldMapScene);

	return ret;
}

// Called before quitting
bool TownScene::CleanUp()
{
	Scene::CleanUp();
	LOG("Freeing scene");
	
	return true;
}
