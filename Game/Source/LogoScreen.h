#ifndef __LOGOSCREEN_H__
#define __LOGOSCREEN_H__

#include "Module.h"

struct SDL_Texture;

class LogoScreen : public Module
{
public:

	LogoScreen();

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
	SDL_Texture* logoScreen;
};

#endif // __LOGOSCREEN_H__