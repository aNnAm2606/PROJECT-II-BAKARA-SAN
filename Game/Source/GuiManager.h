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

	GuiManager(bool startEnabled);

	virtual ~GuiManager();

	bool Awake(pugi::xml_node&) override;
	bool Start() override;
	bool Update(float dt) override;
	bool UpdateAll(float dt,bool logic);
	bool PostUpdate();
	bool CleanUp();

	void OpenPanel(int panel_id);

	bool OnGuiMouseClickEvent(GuiControl* control);

public:


	p2List<GuiPanel*> panels;

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;

	// Gui textures
	SDL_Texture* titleButtons = nullptr;
	SDL_Texture* settingsBox = nullptr;
	SDL_Texture* quitBox = nullptr;
	SDL_Texture* credits = nullptr;
	SDL_Texture* pauseBox = nullptr;
	SDL_Texture* battleBox = nullptr;
	SDL_Texture* loseScreen = nullptr;
	SDL_Texture* victoryScreen = nullptr;
	SDL_Texture* questScreen = nullptr;
	SDL_Texture* inventoryScreen = nullptr;
	SDL_Texture* partyScreen = nullptr;

	int mainFont;
	int numberFont;
	int cursor = 0;
	bool debug = false;
	bool cursorMode = false;

	// Gui panels used
	GuiPanel* titlePanel;
	GuiPanel* settingsPanel;
	GuiPanel* quitPanel;
	GuiPanel* creditsPanel;
	GuiPanel* pausePanel;
	GuiPanel* battlePanel;
	GuiPanel* losePanel;
	GuiPanel* victoryPanel;
	GuiPanel* questPanel;
	GuiPanel* inventoryPanel;
	GuiPanel* partyPanel;

	GuiState lastPanel;

private:
	uint Close_FX = NULL;
	uint Open_FX = NULL;

};

#endif // __GUIMANAGER_H__
