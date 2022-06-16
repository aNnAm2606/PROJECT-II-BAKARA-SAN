#ifndef __TUTORIAL_SCENE_4_H__
#define __TUTORIAL_SCENE_4_H__

#include "Scene.h"
#include "GargoyleBattle_Town_1.h"

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

	bool SaveState(pugi::xml_node& save) override;
	bool LoadState(pugi::xml_node& load) override;
private:
	uint Fade_FX = NULL;

	GargoyleBattle_Town_1 m_Gargoyle;

	Collider* mapCol01;
	Collider* mapCol02;
};

#endif // __TUTORIAL_SCENE_4_H__