#ifndef __ENDSCREEN_H__
#define __ENDSCREEN_H__

#include "Scene.h"


struct SDL_Texture;

class EndScreen : public Scene
{
public:

	EndScreen(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer);

	// Destructor
	virtual ~EndScreen();

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
	int count = 0;
};

#endif // __LOGOSCREEN_H__