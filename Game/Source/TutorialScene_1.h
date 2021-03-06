#ifndef __TUTORIAL_SCENE_1_H__
#define __TUTORIAL_SCENE_1_H__

#include "Scene.h"

#include "GargoyleBattle_Dungeon_1.h"
#include "GargoyleBattle_Dungeon_2.h"

struct SDL_Texture;

class TutorialScene_1 : public Scene
{
public:

	TutorialScene_1(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer);


	// Destructor
	virtual ~TutorialScene_1();

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

	GargoyleBattle_Dungeon_1 m_Gargoyle_1;
	GargoyleBattle_Dungeon_2 m_Gargoyle_2;

	Collider* mapCol01;
	Collider* mapCol02;
	Collider* mapCol03;
	Collider* mapCol04;
	Collider* mapCol05;
};

#endif // __TUTORIAL_SCENE_1_H__