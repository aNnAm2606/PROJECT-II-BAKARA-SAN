#ifndef __BATTLE_MODULE_H__
#define __BATTLE_MODULE_H__

#include "Scene.h"
#include "SDL/include/SDL.h"
#include "Character.h"
#include "PQueue.h"
#include "Quest.h"

#define GRID_WIDTH 2
#define GRID_HEIGHT 4
#define GRID_SIZE GRID_WIDTH*GRID_HEIGHT

#define GRID_PIXEL_SIZE 128

class BattleScene : public Scene
{
private:
	enum EBattleState {
		EBATTLESTATE_WAITING,
		EBATTLESTATE_ATTACKING,
		EBATTLESTATE_NONE
	};

	iPoint m_BattleOffset;

	Character** m_PlayerGrid;
	Character* m_EnemyGrid[GRID_HEIGHT][GRID_WIDTH];

	int m_Rounds;
	int m_EnemyCount;

	PQueue<Character*> m_BattleQueue;
	Character* m_ActiveCharacter;

	EBattleState m_BattleState;

	int m_SelectedAbility;

	void Waiting();
	void Attacking();

	int dim2(int x, int y) { return y * GRID_WIDTH + x; }

	Scene* m_NextScene;
public:
	BattleScene(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer);

	// Destructor
	virtual ~BattleScene();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Damage player at position
	void DamagePlayerAt(iPoint position, int damage);

	// Damage enemy at position
	void DamageEnemyAt(iPoint position, int damage);

	Character* GetActiveCharacter() { return m_ActiveCharacter; }

	void SelectedAbility(int id) { m_SelectedAbility = id; }

	void FakeKill(Character::ECharacterType character);

	void AddEnemy(Character::ECharacterType enemy, int x, int y);

	void SetNextScene(Scene* nscene) { m_NextScene = nscene; }

	QuestCharacterCallbacks onCharacterKilled;
};

#endif // __SCENE_H__