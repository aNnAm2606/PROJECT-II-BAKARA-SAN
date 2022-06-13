#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "Module.h"
#include "External/SDL_mixer\include\SDL_mixer.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f
#define MAX_FX_CHANNELS 56
#define FX_VOLUME 128 // 0-128
#define MUSIC_VOLUME 100 // 0-128

enum SFX
{
	PLAYER_WALK,
	LEVEL_UP,
	TAKE_POTION,
	ENEMY_DIE,
	ENEMY_HIT,
	PLAYER_DIE,
	QUEST_FINISHED,
	GET_ITEM,
	BUTTONDOWN,
	BUTTONFEEDBACK,
	MENU_OPEN,
	MENU_BACK,
	MENU_CLOSED
};

enum Music
{
	OFF = 0,
	DUNGEON1_MUSIC,
	DUNGEON2_MUSIC,
	BATTLE_MUSIC,
	BATTLEBOSS_MUSIC,
	INHOUSE_MUSIC,
	SANCTUARY_MUSIC,
	SHOP_MUSIC,
	TITLE_MUSIC,
	TOWN_MUSIC,
	WORLDMAP_MUSIC,
	FOREST_MUSIC,
	BAR_MUSIC,
	CREDITS_MUSIC
};

struct _Mix_Music;
struct Mix_Chunk;

class Audio : public Module
{
public:

	Audio(bool startEnabled);

	// Destructor
	virtual ~Audio();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called each loop iteration
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fadeTime = DEFAULT_MUSIC_FADE_TIME, float fadeOutTime = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);

	// Change Music track
	bool ChangeMusic(int Id, float fadeInTime = DEFAULT_MUSIC_FADE_TIME, float fadeOutTime = DEFAULT_MUSIC_FADE_TIME);

	// Play Music track spatially (diegetic)
	//bool PlayMusicSpatially(iPoint musicGeneratorPosition);

	int SetMusicVolume(int vol);
	int GetMusicVolume();
	int SetSFXVolume(int vol);
	int GetFxVolume();

private:

	_Mix_Music* music;
	List<Mix_Chunk *>	fx;

public:

	bool playMusicSpatially = false;

	float musicVol = 0;

	float fxVol = 0;
};

#endif // __AUDIO_H__