#ifndef __TOWNSCENE_H__
#define __TOWNSCENE_H__

#include "Scene.h"
#include "Triana.h"
#include "SisterMadonna.h"
#include "StevenWonder.h"
#include "DavidBow.h"
#include "Cat.h"
#include "GargoyleBattle_Town_1.h"

struct SDL_Texture;

class TownScene : public Scene
{
public:

	TownScene(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer);

	// Destructor
	virtual ~TownScene();

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
	

	Triana m_Triana;
	SisterMadonna m_SisterMadonna;
	StevenWonder m_StevenWonder;
	DavidBow m_DavidBow;
	Cat m_Cat;
	GargoyleBattle_Town_1 m_Gargoyle;
};

#endif // __TOWNSCENE_H__
