#include "BattleScene.h"
#include "Chaman.h"
#include "Paladin.h"
#include "FallenAngel.h"
#include "Gargoyle.h"
#include "Render.h"
#include "PlayerModule.h"
#include "GuiManager.h"

#include "App.h"
#include "Input.h"

BattleScene::BattleScene(bool startEnabled) : Module(startEnabled)
{
	name.Create("BattleScene");

	m_BattleOffset = { 200, 200 };
}

BattleScene::~BattleScene()
{
	
}

bool BattleScene::Awake(pugi::xml_node& config)
{
	

	return true;
}

bool BattleScene::Start()
{
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

	m_Rounds = 0;

	m_BattleState = EBattleState::EBATTLESTATE_WAITING;

	return true;
}

bool BattleScene::PreUpdate()
{
	if (m_ActiveCharacter == NULL) {
		Character* c;
		for (int y = 0; y < GRID_HEIGHT; y++) {
			for (int x = 0; x < GRID_WIDTH; x++) {
				c = m_PlayerGrid[y][x];
				if (c) {
					m_BattleQueue.Push(c, c->GetSpeed());
				}

				c = m_EnemyGrid[y][x];
				if (c) {
					m_BattleQueue.Push(c, c->GetSpeed());
				}
			}
		}

		m_Rounds++;
		m_BattleQueue.Pop(m_ActiveCharacter);
	}

	return true;
}
#include <iostream>
bool BattleScene::Update(float dt)
{
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

	return true;
}

void BattleScene::DamagePlayerAt(iPoint position, int damage)
{
	if (!m_PlayerGrid[position.y][position.x]) return;

	m_PlayerGrid[position.y][position.x]->DealDamage(damage);
}

void BattleScene::DamageEnemyAt(iPoint position, int damage)
{
	if (!m_EnemyGrid[position.y][position.x]) return;

	m_EnemyGrid[position.y][position.x]->DealDamage(damage);
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
	m_ActiveCharacter->Update();

	if (!m_ActiveCharacter->IsAttacking()) {
		if (!m_BattleQueue.Pop(m_ActiveCharacter)) {
			m_ActiveCharacter = NULL;
		}

		m_BattleState = EBATTLESTATE_WAITING;
	}
}