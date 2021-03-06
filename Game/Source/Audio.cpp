#include "App.h"
#include "Audio.h"

#include "AssetsManager.h"

#include "Defs.h"
#include "Log.h"

// NOTE: Recommended using: Additional Include Directories,
// instead of 'hardcoding' library location path in code logic
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"

// NOTE: Library linkage is configured in Linker Options
//#pragma comment(lib, "../Game/Source/External/SDL_mixer/libx86/SDL2_mixer.lib")

Audio::Audio(bool startEnabled) : Module(startEnabled)
{
	music = NULL;
	name.Create("audio");
}

// Destructor
Audio::~Audio()
{}

// Called before render is available
bool Audio::Awake(pugi::xml_node& config)
{
	LOG("Loading Audio Mixer");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		active = false;
		ret = true;
	}

	// Load support for the JPG and PNG image formats
	int flags = MIX_INIT_OGG && MIX_INIT_MP3 && MIX_INIT_FLAC;
	int init = Mix_Init(flags);

	if((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		active = false;
		ret = true;
	}

	// Initialize SDL_mixer
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		active = false;
		ret = true;
	}

	SetMusicVolume(128);
	SetSFXVolume(128);

	return ret;
}

bool Audio::Update(float dt)
{

	//if (playMusicSpatially == false) Mix_VolumeMusic(musicVol);


	return true;
}

// Called before quitting
bool Audio::CleanUp()
{
	if(!active)
		return true;

	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	if(music != NULL)
	{
		Mix_FreeMusic(music);
	}

	ListItem<Mix_Chunk*>* item;
	for(item = fx.start; item != NULL; item = item->next)
		Mix_FreeChunk(item->data);

	fx.Clear();

	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);

	return true;
}

// Play a music file
bool Audio::PlayMusic(const char* path, float fadeTime, float fadeOutTime)
{
	bool ret = true;

	if(!active)
		return false;

	if(music != NULL)
	{
		if(fadeTime > 0.0f)
		{
			Mix_FadeOutMusic(int(fadeTime * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		// this call blocks until fade out is done
		Mix_FreeMusic(music);
	}

	if(app->assetsManager->use_pak){
		SDL_RWops* rwops = app->assetsManager->LoadAsset(path);
		music = Mix_LoadMUS_RW(rwops, 1);
	}
	else {
		music = Mix_LoadMUS(path);
	}
	if(music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if(fadeTime > 0.0f)
		{
			if(Mix_FadeInMusic(music, -1, (int) (fadeTime * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if(Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}

// Load WAV
unsigned int Audio::LoadFx(const char* path)
{
	unsigned int ret = 0;

	if(!active)
		return 0;

	Mix_Chunk* chunk = NULL;

	if(app->assetsManager->use_pak){
		SDL_RWops* rwops = app->assetsManager->LoadAsset(path);
		chunk = Mix_LoadWAV_RW(rwops, 1);
	}
	else {
		chunk = Mix_LoadWAV(path);
	}
	

	if(chunk == NULL)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		fx.Add(chunk);
		ret = fx.Count();
	}

	return ret;
}

// Play WAV
bool Audio::PlayFx(unsigned int id, int repeat)
{
	bool ret = false;

	if(!active)
		return false;

	if(id > 0 && id <= fx.Count())
	{
		Mix_PlayChannel(-1, fx[id - 1], repeat);
	}

	return ret;
}

bool Audio::ChangeMusic(int Id, float fadeInTime, float fadeOutTime)
{
	switch (Id)
	{
	case OFF:
	{
		Mix_HaltMusic();
		break;
	}
	case DUNGEON1_MUSIC:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/dungeon.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case DUNGEON2_MUSIC:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/dungeon_1.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case BATTLE_MUSIC:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/battle.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case BATTLEBOSS_MUSIC:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/battle_finalboss.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case INHOUSE_MUSIC:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/safe_house.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case SANCTUARY_MUSIC:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/Sanctuary.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case SHOP_MUSIC:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/shop.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case TITLE_MUSIC:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/title_screen.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case TOWN_MUSIC:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/Town.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case WORLDMAP_MUSIC:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/world_map.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case FOREST_MUSIC:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/forest.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case BAR_MUSIC:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/restaurant.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case CREDITS_MUSIC:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/credits.ogg", fadeInTime, fadeOutTime);

		break;
	}
	}

	return true;
}

//bool Audio::PlayMusicSpatially(iPoint musicGeneratorPosition)
//{
//	int setMusicVolume = MUSIC_VOLUME - (sqrt(pow(app->player->position.x - musicGeneratorPosition.x, 2) + pow(app->player->position.y - musicGeneratorPosition.y, 2)) / 6);
//
//	if (setMusicVolume <= 0) setMusicVolume = 0;
//
//	Mix_VolumeMusic(setMusicVolume);
//
//	return true;
//}

int Audio::SetMusicVolume(int vol)
{
	musicVol = vol;
	Mix_VolumeMusic(vol);

	return musicVol = vol;
}

int Audio::GetMusicVolume()
{
	return musicVol;
}

int Audio::SetSFXVolume(int vol)
{
	fxVol = vol;
	Mix_Volume(-1, vol);

	return fxVol = vol;
}

int Audio::GetFxVolume()
{
	return fxVol;
}

bool Audio::SaveState(pugi::xml_node& save)
{
	save.append_child("music_volume").text() = musicVol;
	save.append_child("fx_volume").text() = fxVol;

	return true;
}

bool Audio::LoadState(pugi::xml_node& load)
{
	musicVol = load.child("music_volume").text().as_int();
	fxVol = load.child("fx_volume").text().as_int();

	SetMusicVolume(musicVol);
	SetSFXVolume(fxVol);

	return true;
}
