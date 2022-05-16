#ifndef __TUTORIAL_SCENE_4_H__
#define __TUTORIAL_SCENE_4_H__

#include "Scene.h"
#include "GargoyleTest.h"

struct SDL_Texture;

class TutorialScene_4 : public Scene
{
public:

	TutorialScene_4(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer);


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
	uint Fade_FX = NULL;

	GargoyleTest m_GargoyleTest;
};

#endif // __TUTORIAL_SCENE_4_H__