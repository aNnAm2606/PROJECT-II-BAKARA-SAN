#include "BattleScene.h"
#include "Chaman.h"
#include "Paladin.h"
#include "Monk.h"
#include "Priest.h"
#include "FallenAngel.h"
#include "Gargoyle.h"
#include "BGhost.h"
#include "Render.h"
#include "PlayerModule.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "TutorialScene_4.h"
#include "TownScene.h"
#include "Transitions.h"

#include "App.h"
#include "Audio.h"
#include "Input.h"
#include "Textures.h"

#include <iostream>

BattleScene::BattleScene(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer) :
	Scene(startEnabled, playerEnabled, name, cameraPos, playerPos, followPlayer)
{
	

	m_BattleOffset = { 200, 200 };

	m_SelectedAbility = -1;
	m_EnemyCount = 0;

	memset(m_EnemyGrid, NULL, GRID_SIZE * 4);
}

BattleScene::~BattleScene()
{
	Scene::~Scene();
}

bool BattleScene::Awake(pugi::xml_node& config)
{
	Scene::Awake(config);

	return true;
}

bool BattleScene::Start()
{
	startCameraPos.x = 0;
	startCameraPos.y = 0;

	Scene::Start();

	app->playerModule->Disable();

	sceneTexture = app->tex->Load("Assets/Art/Maps/fightground.png");

	app->audio->ChangeMusic(BATTLE_MUSIC, 1.0f, 1.0f);

	m_ActiveCharacter = NULL;

	m_Rounds = 0;

	m_BattleState = EBattleState::EBATTLESTATE_WAITING;

	app->currentScene = sceneID::BATTLE;

	m_PlayerGrid = app->playerModule->GetPlayerGrid();

	return true;
}

bool BattleScene::PreUpdate()
{
	Scene::PreUpdate();

	if (m_EnemyCount <= 0) {
		app->fade->Fade(this, m_NextScene);
		return true;
	}

	if (m_ActiveCharacter == NULL) {
		Character* c;
		for (int y = 0; y < GRID_HEIGHT; y++) {
			for (int x = 0; x < GRID_WIDTH; x++) {
				c = m_PlayerGrid[dim2(x,y)];
				if (c != NULL) {
					if (!c->IsDead()) {
						m_BattleQueue.Push(c, c->GetSpeed());
					}

					if (c->Remove()) {
						delete c;
						m_PlayerGrid[dim2(x, y)] = NULL;
					}
				}

				c = m_EnemyGrid[y][x];
				if (c != NULL) {
					if (!c->IsDead()) {
						m_BattleQueue.Push(c, c->GetSpeed());
					}

					if (c->Remove()) {
						delete c;
						m_EnemyGrid[y][x] = NULL;
					}
				}
			}
		}

		m_Rounds++;
		m_BattleQueue.Pop(m_ActiveCharacter);

		if (m_ActiveCharacter->IsPlayer()) {
			app->guiManager->battlePanel->Enable();
		}
		else {
			app->guiManager->battlePanel->Disable();
		}
	}

	return true;
}

bool BattleScene::Update(float dt)
{
	Scene::Update(dt);

	if (!m_ActiveCharacter) return true;

	Character* c;

	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			c = m_PlayerGrid[dim2(x, y)];
			if (c != NULL) {
				c->Update();
			}

			c = m_EnemyGrid[y][x];
			if (c != NULL) {
				c->Update();
			}
		}
	}

	switch (m_BattleState) {
		case EBattleState::EBATTLESTATE_WAITING:
			Waiting();
			break;
		case EBattleState::EBATTLESTATE_ATTACKING:
			Attacking();
			break;
	}

	return true;
}

bool BattleScene::PostUpdate()
{
	Scene::PostUpdate();
	iPoint position;

	// Battle grid
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			Character* c = m_PlayerGrid[dim2(x, y)];

			if (c != NULL) {
				position.x = x * GRID_PIXEL_SIZE + m_BattleOffset.x;
				position.y = y * GRID_PIXEL_SIZE + m_BattleOffset.y;

				m_PlayerGrid[dim2(x, y)]->Render(position);
			}

			c = m_EnemyGrid[y][x];
			if (c != NULL) {
				position.x = x * GRID_PIXEL_SIZE + m_BattleOffset.x + 3 * GRID_PIXEL_SIZE;
				position.y = y * GRID_PIXEL_SIZE + m_BattleOffset.y;

				m_EnemyGrid[y][x]->Render(position);
			}
		}
	}

	// Render effects
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			if (m_PlayerGrid[dim2(x, y)] != NULL) {
				position.x = x * GRID_PIXEL_SIZE + m_BattleOffset.x;
				position.y = y * GRID_PIXEL_SIZE + m_BattleOffset.y;

				m_PlayerGrid[dim2(x, y)]->RenderEffects(position);
			}

			if (m_EnemyGrid[y][x] != NULL) {
				position.x = x * GRID_PIXEL_SIZE + m_BattleOffset.x + 3 * GRID_PIXEL_SIZE;
				position.y = y * GRID_PIXEL_SIZE + m_BattleOffset.y;

				m_EnemyGrid[y][x]->RenderEffects(position);
			}
		}
	}

	if (app->guiManager->back2Title == true)
	{
		app->transitions->SelectTransition(1, 0, 1280, this, (Module*)app->titleScreen);
		app->guiManager->back2Title = false;
	}
	return true;
}

bool BattleScene::CleanUp()
{
	Scene::CleanUp();
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			if (m_EnemyGrid[y][x]) {
				delete m_EnemyGrid[y][x];
				m_EnemyGrid[y][x] = NULL;
			}
		}
	}

	m_EnemyCount = 0;

	app->guiManager->battlePanel->Disable();

	return true;
}

void BattleScene::DamagePlayerAt(iPoint position, int damage)
{
	if (position.x < 0 || position.x >= GRID_WIDTH || position.y < 0 || position.y >= GRID_HEIGHT) return;
	if (!m_PlayerGrid[dim2(position.x, position.y)]) return;
	if (m_PlayerGrid[dim2(position.x, position.y)]->IsDead()) return;

	if (m_PlayerGrid[dim2(position.x, position.y)]->DealDamage(damage)) {
		Character::ECharacterType character_t = m_PlayerGrid[dim2(position.x, position.y)]->getCharacterType();

		std::cout << "[Battle] Character (" << (int)character_t << ") died." << std::endl;

		onCharacterKilled(character_t);
	}
}

void BattleScene::DamageEnemyAt(iPoint position, int damage)
{
	if (position.x < 0 || position.x >= GRID_WIDTH || position.y < 0 || position.y >= GRID_HEIGHT) return;
	if (!m_EnemyGrid[position.y][position.x]) return;
	if (m_EnemyGrid[position.y][position.x]->IsDead()) return;

	if (m_EnemyGrid[position.y][position.x]->DealDamage(damage)) {
		m_EnemyCount--;

		Character::ECharacterType character_t = m_EnemyGrid[position.y][position.x]->getCharacterType();

		std::cout << "[Battle] Character (" << (int)character_t << ") died." << std::endl;

		onCharacterKilled(character_t);
	}
}

void BattleScene::FakeKill(Character::ECharacterType character)
{
	std::cout << "[Battle] Character (" << (int)character << ") died." << std::endl;

	onCharacterKilled(character);
}

void BattleScene::AddEnemy(Character::ECharacterType enemy, int x, int y)
{
	if (m_EnemyGrid[y][x]) return;

	iPoint pos = { x, y };

	Character* c = NULL;

	switch (enemy) {
	case Character::ECharacterType::ECHARACTER_GARGOYLE:
		c = new Gargoyle(pos);
		break;
	case Character::ECharacterType::ECHARACTER_FALLEN_ANGEL:
		c = new FallenAngel(pos);
		break;
	case Character::ECharacterType::ECHARACTER_SPECTRE:
		c = new BGhost(pos);
		break;
	case Character::ECharacterType::ECHARACTER_MIPHARESH:
		break;
	}

	m_EnemyGrid[y][x] = c;
	m_EnemyCount++;
}

void BattleScene::Waiting()
{
	m_ActiveCharacter->SetBattleState(Character::EBattleState::EBATTLESTATE_ACTIVE);

	GamePad& gamepad = app->input->pads[0];
	if (m_ActiveCharacter->IsPlayer()) {
		if (app->input->GamepadConnected() == false)
		{
			if (m_SelectedAbility >= 0) {
				m_BattleState = EBATTLESTATE_ATTACKING;
				m_ActiveCharacter->StartAttack(m_SelectedAbility);

				m_SelectedAbility = -1;
			}
			/*if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
				m_BattleState = EBATTLESTATE_ATTACKING;
				m_ActiveCharacter->StartAttack();
			}*/
		}
		else if (gamepad.a == true)
		{
			m_BattleState = EBATTLESTATE_ATTACKING;
			m_ActiveCharacter->StartAttack();
		}
		
	}
	else {
		m_BattleState = EBATTLESTATE_ATTACKING;
		m_ActiveCharacter->StartAttack();
	}
}

void BattleScene::Attacking()
{
	if (!m_ActiveCharacter->IsAttacking()) {
		m_ActiveCharacter->SetBattleState(Character::EBattleState::EBATTLESTATE_BASE);

		m_ActiveCharacter = NULL;

		while (m_BattleQueue.Pop(m_ActiveCharacter) && m_ActiveCharacter->IsDead());

		if (m_ActiveCharacter) {
			if (m_ActiveCharacter->IsPlayer()) {
				app->guiManager->battlePanel->Enable();
			}else{
				app->guiManager->battlePanel->Disable();
			}
		}

		m_BattleState = EBATTLESTATE_WAITING;
	}
}