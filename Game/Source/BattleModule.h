#ifndef __BATTLE_MODULE_H__
#define __BATTLE_MODULE_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include "Character.h"
#include "PQueue.h"

#define GRID_WIDTH 2
#define GRID_HEIGHT 4
#define GRID_SIZE GRID_WIDTH*GRID_HEIGHT

#define GRID_PIXEL_SIZE 128

class BattleModule : public Module
{
public:
	BattleModule(bool startEnabled);

	// Destructor
	virtual ~BattleModule();

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
private:
	SDL_Texture* m_Background;

	iPoint m_BattleOffset;
	Character* m_PlayerGrid[GRID_HEIGHT][GRID_WIDTH];
	Character* m_EnemyGrid[GRID_HEIGHT][GRID_WIDTH];

	int m_Rounds;

	PQueue<Character*> m_BattleQueue;
	Character* m_ActiveCharacter;

	bool m_ExecuteAttack;
};

#endif // __SCENE_H__