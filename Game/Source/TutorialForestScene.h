#ifndef __TUTORIALFORESTSCENE_H__
#define __TUTORIALFORESTSCENE_H__

#include "Module.h"
#include "AlanParsons.h"

struct SDL_Texture;

class TutorialForestScene : public Module
{
public:

	TutorialForestScene(bool startEnabled);

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
	Point<int> playerPos;
	SDL_Texture* tutorialForestScene;
	AlanParsons m_AlanParsons;
};

#endif // __TUTORIALFORESTSCENE_H__