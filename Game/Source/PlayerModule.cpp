#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeToBlack.h"
#include "PlayerModule.h"
#include "DialogModule.h"
#include "GuiManager.h"
#include "ParticleModule.h"
#include "Particle.h"

#include "BattleScene.h"
#include "InventoryModule.h"
#include "PMQuest1.h"

#include "Defs.h"
#include "Log.h"

#include <iostream>

PlayerModule::PlayerModule(bool startEnabled) : Module(startEnabled)
{
	name.Create("PlayerModule");
	playerCollider = new Collider(playerRect, Collider::PLAYER);
	m_ActiveAnimation = EWalkAnimation::EWALK_DOWN;

	SDL_Rect prect = { 0, 0, 128, 128 };

	// Walking animation
	for (int i = 0; i < 4; i++) {
		prect.y = i * prect.h;

		for (int j = 0; j < 4; j++) {
			prect.x = j * prect.w;
			
			m_WalkAnimations[i].PushBack(prect);
		}

		m_WalkAnimations[i].speed = 0.1f;
	}
}

PlayerModule::~PlayerModule()
{
	delete playerCollider;
}

bool PlayerModule::Awake()
{
	

	return true;
}

bool PlayerModule::Start()
{
	playerSheet = app->tex->Load("Assets/Art/Characters/chaman.png");
	Walking_FX = app->audio->LoadFx("Assets/Audio/Fx/Character_walking.wav");
	playerRect.w = 40;
	playerRect.h = 20;
	playerSpeed = 7;
	playerCollider->rect = playerRect;

	
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
	playerCollider->rect = playerRect;

	return true;
}

bool PlayerModule::Update(float dt)
{
	// Skip cases
	if (app->dialog->IsDialogActive()) return true;
	if (app->guiManager->pausePanel->gamePaused) return true;

	// Update
	GamePad& gamePad = app->input->pads[0];

	m_Moving = false;
	
	if (app->input->GamepadConnected() == false)
	{
		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			if (app->frameCount % 18 == 0) app->audio->PlayFx(Walking_FX);
			playerPos.x += playerSpeed;
			m_ActiveAnimation = EWalkAnimation::EWALK_RIGHT;
			m_Moving = true;
		}
		
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			if (app->frameCount % 18 == 0) app->audio->PlayFx(Walking_FX);
			playerPos.x -= playerSpeed;
			m_ActiveAnimation = EWalkAnimation::EWALK_LEFT;
			m_Moving = true;
		}

		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
			if (app->frameCount % 18 == 0) app->audio->PlayFx(Walking_FX);
			playerPos.y -= playerSpeed;
			m_ActiveAnimation = EWalkAnimation::EWALK_UP;
			m_Moving = true;
		}

		if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
			if (app->frameCount % 18 == 0) app->audio->PlayFx(Walking_FX);
			playerPos.y += playerSpeed;
			m_ActiveAnimation = EWalkAnimation::EWALK_DOWN;
			m_Moving = true;
		}
	}
	else
	{
		if (gamePad.left_x > 0.0f)
		{
			if (app->frameCount % 18 == 0) app->audio->PlayFx(Walking_FX);
			playerPos.x += playerSpeed;
			m_ActiveAnimation = EWalkAnimation::EWALK_LEFT;
			m_Moving = true;
		}
			
		if (gamePad.left_x < 0.0f)
		{
			if (app->frameCount % 18 == 0) app->audio->PlayFx(Walking_FX);
				playerPos.x -= playerSpeed;
				m_ActiveAnimation = EWalkAnimation::EWALK_RIGHT;
				m_Moving = true;
		}
			
		if (gamePad.left_y > 0.0f)
		{
			if (app->frameCount % 18 == 0) app->audio->PlayFx(Walking_FX);
			playerPos.y += playerSpeed;
			m_ActiveAnimation = EWalkAnimation::EWALK_DOWN;
			m_Moving = true;
		}
			
		if (gamePad.left_y < 0.0f)
		{
			if (app->frameCount % 18 == 0) app->audio->PlayFx(Walking_FX);
			playerPos.y -= playerSpeed;
			m_ActiveAnimation = EWalkAnimation::EWALK_UP;
			m_Moving = true;
		}
		
	}

	if (app->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN) {
		app->battleScene->FakeKill(Character::ECharacterType::ECHARACTER_MIPHARESH);
	}

	if (app->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN) {
		app->inventory->AddItem((Item::EItemType)(rand() % Item::EItemType::EITEMTYPE_NONE));
	}

	if (app->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN) {
		Particle p;
		app->particleModule->AddParticle(p, playerPos.x, playerPos.y, 0);
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
	/*SDL_Rect section = { 0,0, 100,120 };
	app->render->DrawTexture(playerSheet, playerRect.x, playerRect.y, &section);*/

	if (m_Moving) {
		m_WalkAnimations[m_ActiveAnimation].Update();
	}
	else {
		m_WalkAnimations[m_ActiveAnimation].Reset();
	}

	SDL_Rect rect = m_WalkAnimations[m_ActiveAnimation].GetCurrentFrame();

	app->render->DrawTexture(playerSheet, playerRect.x, playerRect.y, &rect);

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
