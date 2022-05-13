#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeToBlack.h"
#include "PlayerModule.h"
#include "DialogModule.h"

#include "InventoryModule.h"
#include "PMQuest1.h"

#include "Defs.h"
#include "Log.h"


PlayerModule::PlayerModule(bool startEnabled) : Module(startEnabled)
{
	name.Create("PlayerModule");
}

PlayerModule::~PlayerModule()
{
}

bool PlayerModule::Awake()
{
	

	return true;
}

bool PlayerModule::Start()
{
	playerSheet = app->tex->Load("Assets/Art/Characters/chaman.png");
	playerRect.w = 40;
	playerRect.h = 20;
	playerSpeed = 10;
	
	return true;
}
void PlayerModule::SetPosition(int x, int y)
{
	playerPos.x = x;
	playerPos.y = y;
}
bool PlayerModule::PreUpdate()
{
	playerRect.x = playerPos.x - playerRect.w;
	playerRect.y = playerPos.y - playerRect.h;
	return true;
}

bool PlayerModule::Update(float dt)
{
	// Skip cases
	if (app->dialog->IsDialogActive()) return true;

	// Update
	GamePad& gamePad = app->input->pads[0];
	
	if (app->input->GamepadConnected() == false)
	{
		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT )
			playerPos.x += playerSpeed;
		
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT )
			playerPos.x -= playerSpeed;

		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			playerPos.y -= playerSpeed;

		if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)	
			playerPos.y += playerSpeed;
		
	}
	else
	{
		if (gamePad.left_x > 0.0f)
			playerPos.x += playerSpeed;
		if (gamePad.left_x < 0.0f)
			playerPos.x -= playerSpeed;
		if (gamePad.left_y > 0.0f)
			playerPos.y += playerSpeed;
		if (gamePad.left_y < 0.0f)
		playerPos.y -= playerSpeed;
	}

	if (app->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN) {
		app->inventory->AddItem(Item::EItemType::EITEMTYPE_CAT);
	}
	
	return true;
}
void PlayerModule::GetPosition(int &x, int &y)
{
	x = playerPos.x;
	y = playerPos.y;
}
bool PlayerModule::PostUpdate()
{
	SDL_Rect section = { 0,0, 100,120 };
	app->render->DrawTexture(playerSheet, playerRect.x, playerRect.y, &section);

	return true;
}

bool PlayerModule::CleanUp()
{
	app->tex->UnLoad(playerSheet);
	return true;
}

bool PlayerModule::LoadState(pugi::xml_node& node)
{

	playerPos.x = node.child("position").attribute("x").as_int();
	playerPos.y = node.child("position").attribute("y").as_int();

	return true;
}
bool PlayerModule::SaveState(pugi::xml_node& node)
{
	pugi::xml_node pos = node.append_child("position");

	pos.append_attribute("x").set_value(playerPos.x);
	pos.append_attribute("y").set_value(playerPos.y);

	return true;
}
