#ifndef __TITLESCREEN_H__
#define __TITLESCREEN_H__

#include "Module.h"

struct SDL_Texture;

class TitleScreen : public Module
{
public:

	TitleScreen(bool startEnabled);

	// Destructor
	virtual ~TitleScreen();

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
	SDL_Texture* bg;

public:
	bool startGame = false;
	bool continueGame = false;
};

#endif // __TITLESCREEN_H__