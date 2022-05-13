#ifndef __DUNGEON_SCENE_H__
#define __DUNGEON_SCENE_H__

#include "Scene.h"

struct SDL_Texture;

class DungeonScene : public Scene
{
public:

	DungeonScene(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer);


	// Destructor
	virtual ~DungeonScene();

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

	SDL_Texture* Background1;
	SDL_Texture* Background2;
	SDL_Texture* Background3;
	SDL_Texture* Background4;


};

#endif //__DUNGEON_SCENE_H__