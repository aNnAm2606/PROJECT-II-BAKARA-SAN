#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
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
class BattleModule;
class LogoScreen;
class TitleScreen;
class FadeToBlack;
class GuiManager;
class GameplayScreen;

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

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

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

public:

	// Modules
	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	Audio* audio;
	BattleModule* battleModule;
	LogoScreen* logoScreen;
	TitleScreen* titleScreen;
	GameplayScreen* gameplayScreen;
	FadeToBlack* fade;
	GuiManager* guiManager;

private:

	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module *> modules;

	//Config
	pugi::xml_document configFile;
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

	uint64 frameCount = 0;
	uint32 framesPerSecond = 0;
	uint32 lastSecFrameCount = 0;

	uint32 maxFrameRate;

	float averageFps = 0.0f;
	
};

extern App* app;

#endif	// __APP_H__