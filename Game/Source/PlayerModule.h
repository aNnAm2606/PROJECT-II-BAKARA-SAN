#ifndef __PLAYER_MODULE_H__
#define __PLAYER_MODULE_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include "Point.h"

class PlayerModule : public Module
{
private:
	Point<int> playerPos;
	int playerSpeed;
	SDL_Texture* playerSheet;
	SDL_Rect playerRect;
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

	bool LoadState(pugi::xml_node&) override;
	bool SaveState(pugi::xml_node&) override;
};

#endif // __PLAYER_MODULE_H__