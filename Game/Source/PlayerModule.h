#ifndef __PLAYER_MODULE_H__
#define __PLAYER_MODULE_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include "Point.h"
#include "Collider.h"
#include "Animation.h"

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

	bool m_Moving;
public:
	PlayerModule(bool startEnabled);

	// Destructor
	virtual ~PlayerModule();

	// Called before render is available
	bool Awake();

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
};

#endif // __PLAYER_MODULE_H__