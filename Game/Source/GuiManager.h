#ifndef __GUIMANAGER_H__
#define __GUIMANAGER_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include "p2List.h"
#include "GuiPanel.h"

enum GuiState {
	MAIN_MENU,
	SETTINGS,
	PAUSE,
	QUEST,
	DIALOG,
	GAMEOVER,
	GAME_HUD
};

class GuiManager : public Module
{
public:

	// Constructor
	GuiManager();

	// Destructor
	virtual ~GuiManager();

	// Called before the first frame
	bool Awake(pugi::xml_node&) override;
	bool Start() override;
	bool Update(float dt) override;
	bool UpdateAll(float dt,bool logic);
	bool PostUpdate();
	// Called before quitting
	bool CleanUp();

	void OpenPanel(int panel_id);
	//void OpenPanel(GuiState panel);

	bool OnGuiMouseClickEvent(GuiControl* control);

public:


	p2List<GuiPanel*> panels;

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;

	//Gui textures Used
	SDL_Texture* titleButtons = nullptr;
	SDL_Texture* settingsBox = nullptr;
	SDL_Texture* quitBox = nullptr;
	SDL_Texture* credits = nullptr;
	SDL_Texture* pauseBox = nullptr;

	int mainFont;
	int numberFont;
	bool Debug = false;


	//gui panels used in the game
	GuiPanel* titlePanel;
	GuiPanel* settingsPanel;
	GuiPanel* quitPanel;
	GuiPanel* creditsPanel;
	GuiPanel* pausePanel;

	GuiState lastPanel;

};

#endif // __GUIMANAGER_H__
