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
#include "Transitions.h"

#include "Defs.h"
#include "Log.h"

DungeonScene::DungeonScene(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer) :
	Scene(startEnabled, playerEnabled, name, cameraPos, playerPos, followPlayer)
{
	secretRoomButton = new Collider({ 1600,550, 80, 80 }, Collider::TRIGGER, this);

	secretRoomBottomWall = new Collider({ 1550, 0, 400, 30 }, Collider::WALL);
	secretRoomTopWall = new Collider({ 1550, -300, 400, 30 }, Collider::WALL);
	secretRoomLeftWall = new Collider({ 1550, -400, 10, 400 }, Collider::WALL);
	secretRoomRightWall = new Collider({ 1850, -400, 10, 400 }, Collider::WALL);

	dungeonKey = new Collider({ 1000,-2120, 40,40 }, Collider::TRIGGER);
	keyWall = new Collider({ 0,-2280, 2000,60 }, Collider::WALL);

	lever = new Collider({ 200, -2860, 60,60 }, Collider::TRIGGER);
	leverWall = new Collider({ 0, -2960, 2000,40 }, Collider::WALL);

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
	Lever_FX = app->audio->LoadFx("Assets/Audio/Fx/trigger.wav");
	Pickup_FX = app->audio->LoadFx("Assets/Audio/Fx/get_new_item.wav");

	app->audio->ChangeMusic(DUNGEON1_MUSIC, 1.0f, 1.0f);

	app->currentScene = sceneID::DUNGEON;

	m_Gargoyle.Init();
	m_Gargoyle.SetOriginScene(this);
	m_Gargoyle.SetPosition(1653, -3143);

	return true;
}

// Called each loop iteration
bool DungeonScene::PreUpdate()
{
	Scene::PreUpdate();
	GamePad& gamepad = app->input->pads[0];
	if (secretRoomButton->Intersects(app->playerModule->GetPLayerCollider()->rect))
	{
		app->audio->PlayFx(Lever_FX);
		isSecretRoomOpen = true;
	}
	if (dungeonKey->Intersects(app->playerModule->GetPLayerCollider()->rect))
	{
		keyObtained = true;
		app->audio->PlayFx(Pickup_FX);
	}
	if (lever->Intersects(app->playerModule->GetPLayerCollider()->rect))
	{
		if (app->input->GamepadConnected() == false)
		{
			if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
			{
				app->audio->PlayFx(Lever_FX);
				leverActivated = !leverActivated;
			}
		}
		else if (gamepad.a == true)
		{
			app->audio->PlayFx(Lever_FX);
			leverActivated = !leverActivated;
		}
		
	}
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) { toggleDebug = !toggleDebug; }

	return true;
}

// Called each loop iteration
bool DungeonScene::Update(float dt)
{
	Scene::Update(dt);
	SDL_Rect playerRect = app->playerModule->GetPLayerCollider()->rect;

	m_Gargoyle.Update();

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
	if (keyWall->Intersects(playerRect) && keyObtained == false)
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

	
	if (toggleDebug)
	{
		app->render->DrawRectangle(secretRoomBottomWall->rect, 255, 0, 0);
		app->render->DrawRectangle(secretRoomTopWall->rect, 255, 0, 0);
		app->render->DrawRectangle(secretRoomLeftWall->rect, 255, 0, 0);
		app->render->DrawRectangle(secretRoomRightWall->rect, 255, 0, 0);
		app->render->DrawRectangle(keyWall->rect, 255, 0, 0);
		app->render->DrawRectangle(leverWall->rect, 255, 0, 0);


		app->render->DrawRectangle(dungeonKey->rect, 0, 255, 0);
		app->render->DrawRectangle(secretRoomButton->rect, 0, 255, 0);
		app->render->DrawRectangle(lever->rect, 0, 255, 0);
	}
	else
	{

		if (!keyObtained)
		{
			app->render->DrawTexture(keyTexture, dungeonKey->rect.x, dungeonKey->rect.y, &keySection);
		}
		
		app->render->DrawTexture(leverTexture, lever->rect.x, lever->rect.y, &leverSection);
	}
	

	

	return true;
}

// Called each loop iteration
bool DungeonScene::PostUpdate()
{
	Scene::PostUpdate();
	bool ret = true;
	app->playerModule->GetPosition(playerPos.x, playerPos.y);

	if (playerPos.y > 800) app->fade->Fade(this, (Module*)app->worldMapScene);

	if (app->guiManager->back2Title == true)
	{
		app->transitions->SelectTransition(1, 0, 1280, this, (Module*)app->titleScreen);
		app->guiManager->back2Title = false;
	}

	m_Gargoyle.Render();

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