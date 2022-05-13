#include "BattleScene.h"
#include "Chaman.h"
#include "Paladin.h"
#include "FallenAngel.h"
#include "Gargoyle.h"
#include "BGhost.h"
#include "Render.h"
#include "PlayerModule.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "TutorialScene_4.h"

#include "App.h"
#include "Input.h"

BattleScene::BattleScene(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer) :
	Scene(startEnabled, playerEnabled, name, cameraPos, playerPos, followPlayer)
{
	

	m_BattleOffset = { 200, 200 };
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
	Scene::Start();
	memset(m_PlayerGrid, NULL, GRID_SIZE * 4);
	memset(m_EnemyGrid, NULL, GRID_SIZE * 4);

	m_ActiveCharacter = NULL;

	app->playerModule->Disable();

	app->render->camera.x = 0;
	app->render->camera.y = 0;

	m_PlayerGrid[1][0] = new Chaman();
	m_PlayerGrid[1][1] = new Paladin();

	m_EnemyGrid[0][0] = new Gargoyle();
	m_EnemyGrid[0][1] = new FallenAngel();
	m_EnemyGrid[1][1] = new BGhost();
	m_EnemyCount = 3;

	m_Rounds = 0;

	m_BattleState = EBattleState::EBATTLESTATE_WAITING;

	app->currentScene = sceneID::BATTLE;

	return true;
}

bool BattleScene::PreUpdate()
{
	Scene::PreUpdate();
	if (m_EnemyCount <= 0) {
		app->fade->Fade(this, app->tutorialScene_4);
		return true;
	}

	if (m_ActiveCharacter == NULL) {
		Character* c;
		for (int y = 0; y < GRID_HEIGHT; y++) {
			for (int x = 0; x < GRID_WIDTH; x++) {
				c = m_PlayerGrid[y][x];
				if (c) {
					if (!c->IsDead()) {
						m_BattleQueue.Push(c, c->GetSpeed());
					}

					if (c->Remove()) {
						delete c;
						m_PlayerGrid[y][x] = NULL;
					}
				}

				c = m_EnemyGrid[y][x];
				if (c) {
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
#include <iostream>
bool BattleScene::Update(float dt)
{
	Scene::Update(dt);
	if (!m_ActiveCharacter) return true;

	//
	system("cls");
	Character* c;
	std::cout << "Players" << std::endl;
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			c = m_PlayerGrid[y][x];
			
			if (c) {
				std::cout << c->GetHealth() << std::endl;
			}
		}
	}
	std::cout << "Enemies" << std::endl;
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			c = m_EnemyGrid[y][x];
			if (c) {
				std::cout << c->GetHealth() << std::endl;
			}
		}
	}
	//

	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			c = m_PlayerGrid[y][x];
			if (c) {
				c->Update();
			}

			c = m_EnemyGrid[y][x];
			if (c) {
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
			if (m_PlayerGrid[y][x]) {
				position.x = x * GRID_PIXEL_SIZE + m_BattleOffset.x;
				position.y = y * GRID_PIXEL_SIZE + m_BattleOffset.y;

				m_PlayerGrid[y][x]->Render(position);
			}

			if (m_EnemyGrid[y][x]) {
				position.x = x * GRID_PIXEL_SIZE + m_BattleOffset.x + 3 * GRID_PIXEL_SIZE;
				position.y = y * GRID_PIXEL_SIZE + m_BattleOffset.y;

				m_EnemyGrid[y][x]->Render(position);
			}
		}
	}

	return true;
}

bool BattleScene::CleanUp()
{
	Scene::CleanUp();
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			if (m_PlayerGrid[y][x]) {
				delete m_PlayerGrid[y][x];
			}

			if (m_EnemyGrid[y][x]) {
				delete m_EnemyGrid[y][x];
			}
		}
	}

	app->guiManager->battlePanel->Disable();

	return true;
}

void BattleScene::DamagePlayerAt(iPoint position, int damage)
{
	if (!m_PlayerGrid[position.y][position.x]) return;
	if (m_PlayerGrid[position.y][position.x]->IsDead()) return;

	m_PlayerGrid[position.y][position.x]->DealDamage(damage);
}

void BattleScene::DamageEnemyAt(iPoint position, int damage)
{
	if (!m_EnemyGrid[position.y][position.x]) return;
	if (m_EnemyGrid[position.y][position.x]->IsDead()) return;

	if (m_EnemyGrid[position.y][position.x]->DealDamage(damage)) {
		m_EnemyCount--;
	}
}


void BattleScene::Waiting()
{
	if (m_ActiveCharacter->IsPlayer()) {
		// TODO: SWAP WITH USER INTERFACE
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
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