#include "BattleModule.h"
#include "Chaman.h"
#include "Paladin.h"
#include "FallenAngel.h"
#include "Gargoyle.h"

#include "App.h"
#include "Input.h"

BattleModule::BattleModule(bool startEnabled) : Module(startEnabled)
{
	memset(m_PlayerGrid, NULL, GRID_SIZE * 4);
	memset(m_EnemyGrid, NULL, GRID_SIZE * 4);

	m_BattleOffset = { 200, 200 };
	m_ActiveCharacter = NULL;
	m_ExecuteAttack = false;
}

BattleModule::~BattleModule()
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
}

bool BattleModule::Awake(pugi::xml_node& config)
{
	

	return true;
}

bool BattleModule::Start()
{
	m_PlayerGrid[1][0] = new Chaman();
	m_PlayerGrid[1][1] = new Paladin();

	m_EnemyGrid[0][0] = new Gargoyle();
	m_EnemyGrid[0][1] = new FallenAngel();

	m_Rounds = 0;

	return true;
}

bool BattleModule::PreUpdate()
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
bool BattleModule::Update(float dt)
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

	if (m_ActiveCharacter->IsPlayer()) {
		// TODO: SWAP WITH USER INTERFACE
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			m_ExecuteAttack = true;
		}
	}
	else {
		m_ExecuteAttack = true;
	}

	if (m_ExecuteAttack) {
		m_ActiveCharacter->ExecuteAttack();

		if (!m_ActiveCharacter->IsAttacking()) {
			if (!m_BattleQueue.Pop(m_ActiveCharacter)) {
				m_ActiveCharacter = NULL;
			}

			m_ExecuteAttack = false;
		}
	}

	return true;
}

bool BattleModule::PostUpdate()
{
	iPoint position;

	// Player grid
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			if (m_PlayerGrid[y][x]) {
				position.x = x * GRID_PIXEL_SIZE + m_BattleOffset.x;
				position.y = y * GRID_PIXEL_SIZE + m_BattleOffset.y;

				m_PlayerGrid[y][x]->Render(position);
			}
		}
	}

	// Enemy grid
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			if (m_EnemyGrid[y][x]) {
				position.x = x * GRID_PIXEL_SIZE + m_BattleOffset.x + 3*GRID_PIXEL_SIZE;
				position.y = y * GRID_PIXEL_SIZE + m_BattleOffset.y;

				m_EnemyGrid[y][x]->Render(position);
			}
		}
	}

	return true;
}

bool BattleModule::CleanUp()
{
	return true;
}

void BattleModule::DamagePlayerAt(iPoint position, int damage)
{
	if (!m_PlayerGrid[position.y][position.x]) return;

	m_PlayerGrid[position.y][position.x]->DealDamage(damage);
}

void BattleModule::DamageEnemyAt(iPoint position, int damage)
{
	if (!m_EnemyGrid[position.y][position.x]) return;

	m_EnemyGrid[position.y][position.x]->DealDamage(damage);
}