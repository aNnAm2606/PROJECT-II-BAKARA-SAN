#ifndef __TUTORIAL_SCENE_3_H__
#define __TUTORIAL_SCENE_3_H__

#include "Scene.h"

#include "GargoyleBattle_Dungeon_4.h"

struct SDL_Texture;

class TutorialScene_3 : public Scene
{
public:

	TutorialScene_3(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer);


	// Destructor
	virtual ~TutorialScene_3();

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

	GargoyleBattle_Dungeon_4 m_Gargoyle;

	Collider* mapCol01;
	Collider* mapCol02;
};

#endif // __TUTORIAL_SCENE_3_H__