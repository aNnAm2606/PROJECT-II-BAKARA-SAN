#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeToBlack.h"
#include "PlayerModule.h"
#include "DialogModule.h"


#include "Defs.h"
#include "Log.h"


PlayerModule::PlayerModule(bool startEnabled) : Module(startEnabled)
{
	
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
	playerSheet = app->tex->Load("Assets/Art/Characters/Chaman.png");
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
	SDL_Rect section = { 0,0, 100,120 };
	app->render->DrawTexture(playerSheet, playerRect.x, playerRect.y, &section);
	
	return true;
}
void PlayerModule::GetPosition(int &x, int &y)
{
	x = playerPos.x;
	y = playerPos.y;
}
bool PlayerModule::PostUpdate()
{
	
	return true;
}

bool PlayerModule::CleanUp()
{
	app->tex->UnLoad(playerSheet);
	return true;
}
