#ifndef __PLAYER_MODULE_H__
#define __PLAYER_MODULE_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include "Point.h"
#include "Collider.h"
#include "Animation.h"

#include "BattleScene.h"

class PlayerModule : public Module
{
private:
	Point<int> playerPos;
	int playerSpeed;
	SDL_Texture* playerSheet;
	SDL_Rect playerRect;
	Collider* playerCollider;
	uint Walking_FX = NULL;

	enum EWalkAnimation {
		EWALK_DOWN,
		EWALK_LEFT,
		EWALK_RIGHT,
		EWALK_UP
	};

	Animation m_WalkAnimations[4];
	EWalkAnimation m_ActiveAnimation;

	Character* m_PlayerGrid[GRID_HEIGHT][GRID_WIDTH];

	bool m_Moving;

	bool m_InitPlayers;
public:
	PlayerModule(bool startEnabled);

	// Destructor
	virtual ~PlayerModule();

	// Called before render is available
	bool Awake(pugi::xml_node&);

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

	void SetPosition(int x, int y);
	void GetPosition(int &x, int &y);
	Collider* GetPLayerCollider() { return playerCollider; }

	bool LoadState(pugi::xml_node&) override;
	bool SaveState(pugi::xml_node&) override;

	Character** GetPlayerGrid() { return &m_PlayerGrid[0][0]; }
	Character** GetMonk () { return &m_PlayerGrid[0][1]; }
	Character** GetChaman() { return &m_PlayerGrid[2][0]; }
	Character** GetPaladin() { return &m_PlayerGrid[1][1]; }
	Character** GetPriest() { return &m_PlayerGrid[3][0]; }

	void HealTeam();
};

#endif // __PLAYER_MODULE_H__