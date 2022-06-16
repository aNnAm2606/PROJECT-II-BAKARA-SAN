#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Point.h"
#include "Collider.h"
#include "List.h"
struct SDL_Texture;

class Scene : public Module
{
public:

	Scene(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer);


	// Destructor
	virtual ~Scene();

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



	bool isPlayerEnabled;
	SString sceneName;

	Point<int> startCameraPos;
	Point<int> startPlayerPos;
	Point<bool> startCameraFollowsPlayer;
	
	Point<int> playerPos;
	Point<bool> cameraFollowsPlayer;

	SDL_Texture* sceneTexture = nullptr;
	List <Collider*> colliderList;
private:
	
	
};

#endif // __STARTFORESTSCENE_H__
