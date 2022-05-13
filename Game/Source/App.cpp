#include "App.h"

// Main modules
#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Fonts.h"
#include "Audio.h"
#include "FadeToBlack.h"
#include "DialogModule.h"
#include "GuiManager.h"
#include "ModuleCollisions.h"
#include "AssetsManager.h"

// Player
#include "PlayerModule.h"
#include "InventoryModule.h"
#include "QuestModule.h"

#include "PerfTimer.h"
#include "Defs.h"
#include "Log.h"

#include <iostream>
#include <sstream>

// Battle modules
#include "BattleScene.h"

// Scenes
#include "LogoScreen.h"
#include "TitleScreen.h"
#include "GameplaySceen.h"
#include "StartForestScene.h"
#include "TownScene.h"
#include"TutorialForestScene.h"
#include "TutorialScene_4.h"




// Constructor
App::App(int argc, char* args[]) : argc(argc), args(args)
{
	frames = 0;

	// Main modules
	win = new Window(true);
	input = new Input(true);
	render = new Render(true);
	tex = new Textures(true);
	fonts = new Fonts(true);
	audio = new Audio(true);
	fade = new FadeToBlack(true);
	guiManager = new GuiManager(true);
	collisions = new ModuleCollisions(true);
	assetsManager = new AssetsManager(true);

	// Game modules
	dialog = new DialogModule(true);
	inventory = new InventoryModule(true);
	quests = new QuestModule(true);
	playerModule = new PlayerModule(false);

	// Scenes
	logoScreen = new LogoScreen(true, false, "logoScene", { 0,0 }, { 0,0 }, { false, false });
	titleScreen = new TitleScreen(false, false, "titleScene", { 0,0 }, { 0,0 }, { false, false });
	gameplayScreen = new GameplayScreen(false, false, "gameplayScene", { 0,0 }, { 0,0 }, { false, false });
	startForestScene = new StartForestScene(false, true, "startForestScene", { 400, -200}, { 650, 580 }, { true, true });
	townScene = new TownScene(false, true, "townScene", { -150, -360 }, { 900, 800 }, { true, false });
	tutorialForestScene = new TutorialForestScene(false, true, "tutorialForestScene", { -600, -150 }, { 1700, 600 }, { false, false });
	tutorialScene_4 = new TutorialScene_4(false, true, "tutorialForestScene", { -400, -150 }, { 1600, 450 }, { false, false });
	battleScene = new BattleScene(false, false, "BattleScene", { 0, 0 }, { 0, 0 }, { false, false });

	// Ordered for awake / Start / Update
	// Reverse order of CleanUp

	// Main modules
	AddModule(win);
	AddModule(input);
	AddModule(tex);
	AddModule(fonts);
	AddModule(audio);
	AddModule(guiManager);
	AddModule(collisions);
	AddModule(assetsManager);

	// Scenes
	AddModule(tutorialScene_4);
	AddModule(tutorialForestScene);
	AddModule(townScene);
	AddModule(startForestScene);
	AddModule(titleScreen);
	AddModule(logoScreen);
	AddModule(gameplayScreen);
	AddModule(battleScene);
	
	// Game modules
	//AddModule(battleModule);
	AddModule(playerModule);
	AddModule(dialog);
	AddModule(inventory);
	AddModule(quests);

	// FadeToBlack
	AddModule(fade);

	// Render last to swap buffer
	AddModule(render);

	frameDuration = new PerfTimer();
	maxFrameRate = 60;
}

// Destructor
App::~App()
{
	// Release modules
	ListItem<Module*>* item = modules.end;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->prev;
	}
	scenes.Clear();
	modules.Clear();
}

void App::AddModule(Module* module)
{
	module->Init();
	modules.Add(module);
}
void App::AddScene(Module* scene)
{
	scenes.Add(scene);
}

// Called before render is available
bool App::Awake()
{
	// TODO 3: Load config from XML
	bool ret = LoadConfig();

	if(ret == true)
	{
		// TODO 4: Read the title from the config file
		title.Create(configApp.child("title").child_value());
		win->SetTitle(title.GetString());

		ListItem<Module*>* item;
		item = modules.start;

		while(item != NULL && ret == true)
		{
			// TODO 5: Add a new argument to the Awake method to receive a pointer to an xml node.
			// If the section with the module name exists in config.xml, fill the pointer with the valid xml_node
			// that can be used to read all variables for that module.
			// Send nullptr if the node does not exist in config.xml
			ret = item->data->Awake(config.child(item->data->name.GetString()));
			item = item->next;
		}
	}
	
	return ret;
}

// Called before the first frame
bool App::Start()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;

	while(item != NULL && ret == true)
	{
		if (item->data->IsEnabled())
			ret = item->data->Start();
		item = item->next;
	}

	currentScene = sceneID::LOGO;
	return ret;
}

// Called each loop iteration
bool App::Update()
{
	bool ret = true;
	PrepareUpdate();

	if(input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if(ret == true)
		ret = PreUpdate();

	if(ret == true)
		ret = DoUpdate();

	if(ret == true)
		ret = PostUpdate();

	FinishUpdate();
	return ret;
}

// Load config from XML file
bool App::LoadConfig()
{
	bool ret = true;

	// TODO 3: Load config.xml file using load_file() method from the xml_document class
	pugi::xml_parse_result result = configFile.load_file("config.xml");

	// TODO 3: Check result for loading errors
	if(result == NULL)
	{
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
		ret = false;
	}
	else
	{
		config = configFile.child("config");
		configApp = config.child("app");
	}

	return ret;
}

// ---------------------------------------------
void App::PrepareUpdate()
{
	frameCount++;
	lastSecFrameCount++;

	// Calculate the dt: differential time since last frame
	dt = frameDuration->ReadMs();
	frameDuration->Start();
}

// ---------------------------------------------
void App::FinishUpdate()
{
	// This is a good place to call Load / Save functions

	if (loadRequest)
	{
		
		if (!sceneLoaded || app->titleScreen->continueGame) 
			LoadSavedScene();
		
		if (sceneLoaded)
		{
			LoadFromFile();
			sceneLoaded = false;
			loadRequest = false;
			
		}
		
		
	}
	if (saveRequest)
	{
		//SaveCurrentScene();
		SaveToFile();
		savedScene = currentScene;
		saveRequest = false;
	}
	float secondsSinceStartup = startupTime.ReadSec();

	if (lastSecFrameTime.Read() > 1000) {
		lastSecFrameTime.Start();
		framesPerSecond = lastSecFrameCount;
		lastSecFrameCount = 0;
		averageFps = (averageFps + framesPerSecond) / 2;
	}

	static char title[256];
	sprintf_s(title, 256, "BAKARA-SAN PROJECT - Av.FPS: %.2f Last sec frames: %i Last dt: %.3f Time since startup: %.3f Frame Count: %I64u ",
		averageFps, framesPerSecond, dt, secondsSinceStartup, frameCount);
	dtSeconds = dt / 1000;

	float delay = float(1000 / maxFrameRate) - frameDuration->ReadMs();
	
	PerfTimer* delayt = new PerfTimer();
	delayt->Start();
	if (maxFrameRate > 0 && delay > 0) SDL_Delay(delay);
	LOG("Expected %f milliseconds and the real delay is % f", delay, delayt->ReadMs());

	app->win->SetTitle(title);
}



// Call modules before each loop iteration
bool App::PreUpdate()
{
	bool ret = true;

	ListItem<Module*>* item;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}
		if (item->data->IsEnabled())
			ret = item->data->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool App::DoUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}
		if (item->data->IsEnabled())
			ret = item->data->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool App::PostUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}
		if (item->data->IsEnabled())
			ret = item->data->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool App::CleanUp()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.end;

	while(item != NULL && ret == true)
	{
		if (item->data->IsEnabled())
			ret = item->data->CleanUp();
		item = item->prev;
	}

	return ret;
}

// ---------------------------------------
int App::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* App::GetArgv(int index) const
{
	if(index < argc)
		return args[index];
	else
		return NULL;
}

// ---------------------------------------
const char* App::GetTitle() const
{
	return title.GetString();
}

// ---------------------------------------
const char* App::GetOrganization() const
{
	return organization.GetString();
}

void App::LoadGameRequest()
{
	loadRequest = true;
}
void App::SaveGameRequest() const
{
	saveRequest = true;
}


// L02: TODO 5: Implement the method LoadFromFile() to actually load an xml file
// then call all the modules to load themselves
bool App::LoadFromFile()
{
	bool ret = true;
	pugi::xml_parse_result result = gameStateFile.load_file("save_game.xml");
	
	currentScene = (sceneID) gameStateFile.child("game_state").child("Scene").attribute("id").as_int();

	if (result == NULL)
	{
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
		ret = false;
	}

	ListItem<Module*>* item;
	item = modules.start;

	while (item != NULL && ret == true)
	{
		//pugi::xml_node moduleNode = saveStateNode.child(item->data->name.GetString());
		ret = item->data->LoadState(gameStateFile.child("game_state").child(item->data->name.GetString()));
		//ret = item->data->LoadState(moduleNode);
		item = item->next;
	}

	
	return ret;


}

bool App::SaveToFile() const
{
	bool ret = false;
	pugi::xml_document* saveDoc = new pugi::xml_document();
	pugi::xml_node saveStateNode = saveDoc->append_child("game_state");

	ListItem<Module*>* item;
	item = modules.start;

	saveStateNode.append_child("Scene").append_attribute("id").set_value(currentScene);
	
	
	while (item != NULL)
	{
		//pugi::xml_node moduleNode = saveStateNode.child(item->data->name.GetString());
		ret = item->data->SaveState(saveStateNode.append_child(item->data->name.GetString()));
		item = item->next;
	}
	ret = saveDoc->save_file("save_game.xml");
	
	return ret;

}

bool App::SaveCurrentScene(pugi::xml_node& node)
{
	bool ret = true;
	savedScene = currentScene;
	
	return ret;
}

bool App::LoadSavedScene()
{
	bool ret = true;
	Module* current = logoScreen;

	pugi::xml_parse_result result = gameStateFile.load_file("save_game.xml");

	savedScene = (sceneID)gameStateFile.child("game_state").child("Scene").attribute("id").as_int();

	switch (currentScene)
	{
	case LOGO: current = logoScreen;
		break;
	case TITLE: current = titleScreen;
		break;
	case GAMEPLAY: current = gameplayScreen;
		break;
	case BATTLE: current = battleScene;
		break;
	case START_FOREST: current = startForestScene;
		break;
	case TOWN: current = townScene;
		break;

	case TUTORIAL_FOREST: current = tutorialForestScene;
		break;
	case TUTORIAL_4: current = tutorialScene_4;
		break;
	default: current = logoScreen;
		break;
	}

	if (currentScene != savedScene)
	{
		switch (savedScene)
		{
		case LOGO: fade->Fade(current, logoScreen);
			break;
		case TITLE:fade->Fade(current, titleScreen);
			break;
		case GAMEPLAY: fade->Fade(current, gameplayScreen);
			break;
		case BATTLE: fade->Fade(current, battleScene);
			break;
		case START_FOREST: fade->Fade(current, startForestScene);
			break;
		case TOWN: fade->Fade(current, townScene);
			break;
		case TUTORIAL_FOREST: fade->Fade(current, tutorialForestScene);
			break;
		case TUTORIAL_4: fade->Fade(current, tutorialScene_4);
			break;
		default: ret = false;
			break;
		}
	}
	else
	{
		sceneLoaded = true;
	}
	
	
	
	return ret;
}

