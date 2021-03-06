#ifndef __GAMEPLAYSCREEN_H__
#define __GAMEPLAYSCREEN_H__

#include "Scene.h"

struct SDL_Texture;

class GameplayScreen : public Scene
{
public:

	GameplayScreen(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer);

	// Destructor
	virtual ~GameplayScreen();

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

private:

};

#endif // __GAMEPLAYSCREEN_H__