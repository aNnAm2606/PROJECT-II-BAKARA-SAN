#ifndef __LOGOSCREEN_H__
#define __LOGOSCREEN_H__

#include "Module.h"

struct SDL_Texture;

class LogoScreen : public Module
{
public:

	LogoScreen(bool startEnabled);

	// Destructor
	virtual ~LogoScreen();

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

	SDL_Texture* logoScreen;

	uint Logo_FX = NULL;
};

#endif // __LOGOSCREEN_H__