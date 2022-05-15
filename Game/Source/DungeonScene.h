#ifndef __DUNGEON_SCENE_H__
#define __DUNGEON_SCENE_H__

#include "Scene.h"
#include "Collider.h"

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
	
	SDL_Texture* background1;
	SDL_Texture* background2;
	SDL_Texture* background3;
	SDL_Texture* background4;

	SDL_Texture* keyTexture;
	SDL_Texture* leverTexture;

	List <Collider*> colliderList;

	Collider* secretRoomButton;
	Collider* secretRoomBottomWall;
	Collider* secretRoomTopWall;
	Collider* secretRoomLeftWall;
	Collider* secretRoomRightWall;
	
	Collider* dungeonKey;
	Collider* keyWall;

	Collider* lever;
	Collider* leverWall;

	
	bool isSecretRoomOpen = false;
	bool keyObtained = false;
	bool leverActivated = false;

	bool toggleDebug;


};

#endif //__DUNGEON_SCENE_H__