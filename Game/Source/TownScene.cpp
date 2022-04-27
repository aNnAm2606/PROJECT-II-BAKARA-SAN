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

TownScene::TownScene(bool startEnabled) : Module(startEnabled)
{
	name.Create("TownScene");
}

// Destructor
TownScene::~TownScene()
{}

// Called before render is available
bool TownScene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool TownScene::Start()
{
	app->render->camera.x = -150;
	app->render->camera.y = -360;
	app->playerModule->Enable();
	app->playerModule->SetPosition(900, 800);
	

	townScene = app->tex->Load("Assets/Art/Maps/town_map.png");

	app->render->followPlayerX = true;
	app->render->followPlayerY = false;

	app->audio->ChangeMusic(TOWN_MUSIC, 1.0f, 1.0f);

	m_Triana.Init();
	m_SisterMadonna.Init();

	app->currentScene = sceneID::TOWN;

	return true;
}

// Called each loop iteration
bool TownScene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool TownScene::Update(float dt)
{
	m_Triana.Update();
	m_SisterMadonna.Update();
	
	app->render->DrawTexture(townScene, 0, 0, NULL);
	m_SisterMadonna.Render();
	m_Triana.Render();

	app->playerModule->GetPosition(playerPos.x, playerPos.y);
	if (playerPos.x < 650 || playerPos.x > 1275) app->render->followPlayerX = false;
	else app->render->followPlayerX = true;

	if (playerPos.y < 375 || playerPos.y > 710) app->render->followPlayerY = false;
	else app->render->followPlayerY = true;



	return true;
}

// Called each loop iteration
bool TownScene::PostUpdate()
{
	bool ret = true;
	
	if (playerPos.x < 0)app->fade->Fade(this, (Module*) app->tutorialForestScene);
	if (playerPos.y > 1000)app->fade->Fade(this, (Module*) app->startForestScene);

	return ret;
}

// Called before quitting
bool TownScene::CleanUp()
{
	LOG("Freeing scene");
	app->tex->UnLoad(townScene);
	return true;
}
