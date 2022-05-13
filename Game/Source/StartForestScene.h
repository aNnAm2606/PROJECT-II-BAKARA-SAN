#ifndef __STARTFORESTSCENE_H__
#define __STARTFORESTSCENE_H__

#include "Module.h"
#include "Scene.h"

struct SDL_Texture;

class StartForestScene : public Scene
{
public:

	StartForestScene(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer);
	

	// Destructor
	virtual ~StartForestScene();

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

#endif // __STARTFORESTSCENE_H__