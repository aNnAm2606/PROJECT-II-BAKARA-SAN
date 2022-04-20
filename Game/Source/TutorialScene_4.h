#ifndef __TUTORIAL_SCENE_4_H__
#define __TUTORIAL_SCENE_4_H__
#include "Module.h"

struct SDL_Texture;

class TutorialScene_4 : public Module
{
public:

	TutorialScene_4(bool startEnabled);


	// Destructor
	virtual ~TutorialScene_4();

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
	SDL_Texture* tutorialScene_4;
	Point<int>playerPos;
};

#endif // __TUTORIAL_SCENE_4_H__