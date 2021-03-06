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

#include "Chaman.h"
#include "Paladin.h"
#include "Monk.h"
#include "Priest.h"

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

	m_InitPlayers = true;
}

PlayerModule::~PlayerModule()
{
	delete playerCollider;
}

bool PlayerModule::Awake(pugi::xml_node& config)
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

	// Init playergrid
	if (m_InitPlayers) {
		memset(m_PlayerGrid, NULL, GRID_SIZE * 4);

		m_PlayerGrid[0][1] = new Monk({ 1, 0 });
		m_PlayerGrid[2][0] = new Chaman({ 0,2 });
		m_PlayerGrid[1][1] = new Paladin({ 1,1 });
		m_PlayerGrid[3][0] = new Priest({ 0, 3 });

		m_InitPlayers = false;
	}

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
			m_ActiveAnimation = EWalkAnimation::EWALK_UP;
			m_Moving = true;
		}
			
		if (gamePad.left_y < 0.0f)
		{
			if (app->frameCount % 18 == 0) app->audio->PlayFx(Walking_FX);
			playerPos.y -= playerSpeed;
			m_ActiveAnimation = EWalkAnimation::EWALK_DOWN;
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

	pugi::xml_node& team = node.child("team");

	// Init playergrid
	memset(m_PlayerGrid, NULL, GRID_SIZE * 4);

	Stats stats;

	m_PlayerGrid[0][1] = new Monk({ 1, 0 });
	stats.health = team.child("monk").attribute("health").as_int();
	stats.maxHealth = team.child("monk").attribute("maxHealth").as_int();
	stats.damage = team.child("monk").attribute("damage").as_int();
	stats.speed = team.child("monk").attribute("speed").as_int();
	m_PlayerGrid[0][1]->SetStats(stats);

	m_PlayerGrid[2][0] = new Chaman({ 0,2 });
	stats.health = team.child("chaman").attribute("health").as_int();
	stats.maxHealth = team.child("chaman").attribute("maxHealth").as_int();
	stats.damage = team.child("chaman").attribute("damage").as_int();
	stats.speed = team.child("chaman").attribute("speed").as_int();
	m_PlayerGrid[2][0]->SetStats(stats);

	m_PlayerGrid[1][1] = new Paladin({ 1,1 });
	stats.health = team.child("paladin").attribute("health").as_int();
	stats.maxHealth = team.child("paladin").attribute("maxHealth").as_int();
	stats.damage = team.child("paladin").attribute("damage").as_int();
	stats.speed = team.child("paladin").attribute("speed").as_int();
	m_PlayerGrid[1][1]->SetStats(stats);

	m_PlayerGrid[3][0] = new Priest({ 0, 3 });
	stats.health = team.child("priest").attribute("health").as_int();
	stats.maxHealth = team.child("priest").attribute("maxHealth").as_int();
	stats.damage = team.child("priest").attribute("damage").as_int();
	stats.speed = team.child("priest").attribute("speed").as_int();
	m_PlayerGrid[3][0]->SetStats(stats);

	m_InitPlayers = false;

	return true;
}
bool PlayerModule::SaveState(pugi::xml_node& node)
{
	pugi::xml_node pos = node.append_child("position");

	pos.append_attribute("x").set_value(playerPos.x);
	pos.append_attribute("y").set_value(playerPos.y);

	pugi::xml_node team = node.append_child("team");

	// Monk
	pugi::xml_node monk = team.append_child("monk");
	monk.append_attribute("health") = m_PlayerGrid[0][1]->GetHealth();
	monk.append_attribute("maxHealth") = m_PlayerGrid[0][1]->GetMaxHealth();
	monk.append_attribute("damage") = m_PlayerGrid[0][1]->GetDamage();
	monk.append_attribute("speed") = m_PlayerGrid[0][1]->GetSpeed();

	// Chaman
	pugi::xml_node chaman = team.append_child("chaman");
	chaman.append_attribute("health") = m_PlayerGrid[2][0]->GetHealth();
	chaman.append_attribute("maxHealth") = m_PlayerGrid[2][0]->GetMaxHealth();
	chaman.append_attribute("damage") = m_PlayerGrid[2][0]->GetDamage();
	chaman.append_attribute("speed") = m_PlayerGrid[2][0]->GetSpeed();

	// Paladin
	pugi::xml_node paladin = team.append_child("paladin");
	paladin.append_attribute("health") = m_PlayerGrid[1][1]->GetHealth();
	paladin.append_attribute("maxHealth") = m_PlayerGrid[1][1]->GetMaxHealth();
	paladin.append_attribute("damage") = m_PlayerGrid[1][1]->GetDamage();
	paladin.append_attribute("speed") = m_PlayerGrid[1][1]->GetSpeed();

	// Priest
	pugi::xml_node priest = team.append_child("priest");
	priest.append_attribute("health") = m_PlayerGrid[3][0]->GetHealth();
	priest.append_attribute("maxHealth") = m_PlayerGrid[3][0]->GetMaxHealth();
	priest.append_attribute("damage") = m_PlayerGrid[3][0]->GetDamage();
	priest.append_attribute("speed") = m_PlayerGrid[3][0]->GetSpeed();

	return true;
}

void PlayerModule::HealTeam()
{
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			Character* c = m_PlayerGrid[y][x];

			if (c) {
				c->FullHeal();
			}
		}
	}
}

void PlayerModule::HealTeam(int value)
{
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			Character* c = m_PlayerGrid[y][x];

			if (c) {
				c->Heal(value);
			}
		}
	}
}