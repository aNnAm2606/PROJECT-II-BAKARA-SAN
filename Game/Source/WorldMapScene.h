#ifndef __WORLD_MAP_SCENE_H__
#define __WORLD_MAP_SCENE_H__

#include "Scene.h"

struct SDL_Texture;

class WorldMapScene : public Scene
{
public:

	WorldMapScene(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer);


	// Destructor
	virtual ~WorldMapScene();

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



};

#endif //__WORLD_MAP_SCENE_H__