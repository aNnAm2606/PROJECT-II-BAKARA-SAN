#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeToBlack.h"
#include "DungeonScene.h"
#include "GuiManager.h"
#include "PlayerModule.h"
#include "Point.h"

#include "Defs.h"
#include "Log.h"

DungeonScene::DungeonScene(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer) :
	Scene(startEnabled, playerEnabled, name, cameraPos, playerPos, followPlayer)
{
	secretRoomButton = new Collider({ 1600,550, 80, 80 }, Collider::TRIGGER, this);

	secretRoomBottomWall = new Collider({ 1550, 0, 200, 30 }, Collider::WALL);
	secretRoomTopWall = new Collider({ 1550, -200, 200, 30 }, Collider::WALL);
	secretRoomLeftWall = new Collider({ 1550, -200, 10, 200 }, Collider::WALL);
	secretRoomRightWall = new Collider({ 1750, -200, 10, 200 }, Collider::WALL);

	dungeonKey = new Collider({ 1000,1120, 40,40 }, Collider::TRIGGER);
	keyWall = new Collider({ 0,1080, 2000,60 }, Collider::WALL);

	lever = new Collider({ 200, 2560, 60,60 }, Collider::TRIGGER);
	leverWall = new Collider({ 0, 2460, 40,40 }, Collider::WALL);

	colliderList.Add(secretRoomButton);
	colliderList.Add(secretRoomBottomWall);
	colliderList.Add(secretRoomTopWall);
	colliderList.Add(secretRoomLeftWall);
	colliderList.Add(secretRoomRightWall);
	colliderList.Add(dungeonKey);
	colliderList.Add(keyWall);
	colliderList.Add(lever);
	colliderList.Add(leverWall);
}

// Destructor
DungeonScene::~DungeonScene()
{
	Scene::~Scene();
	colliderList.Clear();

}

// Called before render is available
bool DungeonScene::Awake(pugi::xml_node& config)
{
	Scene::Awake(config);
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool DungeonScene::Start()
{
	Scene::Start();

	
	background1 = app->tex->Load("Assets/Art/Maps/dungeon_map_1.png");
	background2 = app->tex->Load("Assets/Art/Maps/dungeon_map_2.png");
	background3 = app->tex->Load("Assets/Art/Maps/dungeon_map_3.png");
	background4 = app->tex->Load("Assets/Art/Maps/dungeon_map_4.png");

	keyTexture = app->tex->Load("Assets/Art/Items/items.png");
	leverTexture = app->tex->Load("Assets/Art/Items/weapons.png");

	app->audio->ChangeMusic(DUNGEON_MUSIC, 1.0f, 1.0f);

	app->currentScene = sceneID::DUNGEON;
	return true;
}

// Called each loop iteration
bool DungeonScene::PreUpdate()
{
	Scene::PreUpdate();
	
	if (secretRoomButton->Intersects(app->playerModule->GetPLayerCollider()->rect))
	{
		isSecretRoomOpen = true;
	}
	if (dungeonKey->Intersects(app->playerModule->GetPLayerCollider()->rect))
	{
		KeyObtained = true;
	}
	if (lever->Intersects(app->playerModule->GetPLayerCollider()->rect))
	{
		if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
		{
			leverActivated = !leverActivated;
		}
	}


	return true;
}

// Called each loop iteration
bool DungeonScene::Update(float dt)
{
	Scene::Update(dt);
	SDL_Rect playerRect = app->playerModule->GetPLayerCollider()->rect;




	if (secretRoomBottomWall->Intersects(playerRect) && isSecretRoomOpen == false)
	{
		app->playerModule->SetPosition(playerPos.x, playerPos.y + 20);
	}
	if (secretRoomLeftWall->Intersects(playerRect))
	{
		app->playerModule->SetPosition(playerPos.x - 20, playerPos.y);
	}
	if (secretRoomTopWall->Intersects(playerRect))
	{
		app->playerModule->SetPosition(playerPos.x, playerPos.y - 20);
	}
	if (secretRoomRightWall->Intersects(playerRect))
	{
		app->playerModule->SetPosition(playerPos.x + 20, playerPos.y);
	}
	if (keyWall->Intersects(playerRect) && KeyObtained == false)
	{
		app->playerModule->SetPosition(playerPos.x, playerPos.y + 20);
	}
	if (leverWall->Intersects(playerRect) && leverActivated == false)
	{
		app->playerModule->SetPosition(playerPos.x, playerPos.y + 20);
	}



	if (playerPos.x < 700 || playerPos.x > 1250) cameraFollowsPlayer.x = false;
	else cameraFollowsPlayer.x = true;

	if (playerPos.y < -2850 || playerPos.y > 700) cameraFollowsPlayer.y = false;
	else cameraFollowsPlayer.y = true;

	SDL_Rect leverSection = { 56,80, 30,50 };
	SDL_Rect keySection = { 105,85,30,30 };
	app->render->DrawTexture(background4, 0, 0, NULL);
	app->render->DrawTexture(background3, 0, -1080, NULL);
	app->render->DrawTexture(background2, 0, -2160, NULL);
	app->render->DrawTexture(background1, 0, -3240, NULL);
	app->render->DrawTexture(leverTexture, lever->rect.x, lever->rect.y, &leverSection);
	app->render->DrawTexture(keyTexture, dungeonKey->rect.x, dungeonKey->rect.y, &keySection);

	

	return true;
}

// Called each loop iteration
bool DungeonScene::PostUpdate()
{
	Scene::PostUpdate();
	bool ret = true;
	app->playerModule->GetPosition(playerPos.x, playerPos.y);

	if (playerPos.y > 800) app->fade->Fade(this, (Module*)app->worldMapScene);


	return ret;
}

// Called before quitting
bool DungeonScene::CleanUp()
{
	Scene::CleanUp();
	LOG("Freeing scene");

	app->tex->UnLoad(background4);
	app->tex->UnLoad(background3);
	app->tex->UnLoad(background2);
	app->tex->UnLoad(background1);

	app->tex->UnLoad(keyTexture);
	app->tex->UnLoad(leverTexture);

	app->guiManager->pausePanel->Disable();

	return true;
}