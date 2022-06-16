#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "Scene.h"
#include "List.h"

#include "PerfTimer.h"
#include "Timer.h"
#include "PugiXml/src/pugixml.hpp"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class ModuleCollisions;
class GuiManager;
class Fonts;
class DialogModule;
class FadeToBlack;
class PlayerModule;
class BattleScene;
class AssetsManager;
class InventoryModule;
class QuestModule;
class Transitions;
class ParticleModule;

//Scenes
class LogoScreen;
class TitleScreen;
class EndScreen;
class StartForestScene;
class TownScene;
class GameplayScreen;
class TutorialForestScene;
class TutorialScene_1;
class TutorialScene_2;
class TutorialScene_3;
class TutorialScene_4;
class WorldMapScene;
class DungeonScene;
enum  sceneID
{
	LOGO,
	TITLE,
	GAMEPLAY,
	BATTLE,
	START_FOREST,
	TOWN,
	TUTORIAL_FOREST,
	TUTORIAL_1,
	TUTORIAL_2,
	TUTORIAL_3,
	TUTORIAL_4,
	WORLD_MAP,
	DUNGEON,
	END
};
class App
{
public:

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	//Add a new scene to the scene list
	void AddScene(Module* scene);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	void LoadGameRequest();
	void SaveGameRequest() const;

	void SceneLoadFinish();

private:

	// Load config file
	bool LoadConfig();

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	bool LoadFromFile();

	bool SaveToFile() const;

	bool SaveCurrentScene(pugi::xml_node&);

	bool LoadSavedScene();

	

	

public:

	// Modules
	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	Fonts* fonts;
	Audio* audio;
	GuiManager* guiManager;
	DialogModule* dialog;
	FadeToBlack* fade;
	ModuleCollisions* collisions;
	PlayerModule* playerModule;
	AssetsManager* assetsManager;
	InventoryModule* inventory;
	QuestModule* quests;
	Transitions* transitions;
	ParticleModule* particleModule;

	//Scenes
	LogoScreen* logoScreen;
	TitleScreen* titleScreen;
	GameplayScreen* gameplayScreen;
	StartForestScene* startForestScene;
	TownScene* townScene;
	TutorialForestScene* tutorialForestScene;
	TutorialScene_1* tutorialScene_1;
	TutorialScene_2* tutorialScene_2;
	TutorialScene_3* tutorialScene_3;
	TutorialScene_4* tutorialScene_4;
	WorldMapScene* worldMapScene;
	DungeonScene* dungeonScene;
	BattleScene* battleScene;
	EndScreen* endScreen;

	sceneID currentScene;
	sceneID savedScene;

	uint64 frameCount = 0;

private:

	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module *> modules;
	List<Module *> scenes;

	//Config
	pugi::xml_document configFile;
	pugi::xml_document gameStateFile;
	pugi::xml_node config;
	pugi::xml_node configApp;



	//FPS control
	uint frames;
	float dt;
	float dtSeconds;

	PerfTimer* ptimer;
	PerfTimer* frameDuration;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;

	uint32 framesPerSecond = 0;
	uint32 lastSecFrameCount = 0;

	uint32 maxFrameRate;

	float averageFps = 0.0f;

	//Save-Load
	mutable bool saveRequest = false;
	bool loadRequest = false;

	bool sceneLoaded;
	
	
};

extern App* app;

#endif	// __APP_H__