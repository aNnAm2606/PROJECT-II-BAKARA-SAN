#ifndef __TUTORIALFORESTSCENE_H__
#define __TUTORIALFORESTSCENE_H__

#include "Scene.h"
#include "AlanParsons.h"

struct SDL_Texture;

class TutorialForestScene : public Scene
{
public:

	TutorialForestScene(bool startEnabled, bool playerEnabled, SString name, Point<int> cameraPos, Point<int>playerPos, Point<bool> followPlayer);

	// Destructor
	virtual ~TutorialForestScene();

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
	AlanParsons m_AlanParsons;
};

#endif // __TUTORIALFORESTSCENE_H__