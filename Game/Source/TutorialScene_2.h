#ifndef __TUTORIAL_SCENE_2_H__
#define __TUTORIAL_SCENE_2_H__

#include "Scene.h"

struct SDL_Texture;

class TutorialScene_2 : public Scene
{
public:

	TutorialScene_2(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer);


	// Destructor
	virtual ~TutorialScene_2();

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
	uint Fade_FX = NULL;


};

#endif // __TUTORIAL_SCENE_2_H__