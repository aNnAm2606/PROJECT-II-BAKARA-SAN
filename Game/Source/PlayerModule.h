#ifndef __PLAYER_MODULE_H__
#define __PLAYER_MODULE_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class PlayerModule : public Module
{
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

private:
	SDL_Texture* playerSheet;
	SDL_Rect playerRect;
};

#endif // __SCENE_H__