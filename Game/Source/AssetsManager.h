#ifndef __ASSETSMANAGER_H__
#define __ASSETSMANAGER_H__

#include "Module.h"

struct SDL_RWops;

class AssetsManager : public Module
{
public:

	AssetsManager(bool start_enabled);

	// Destructor
	virtual ~AssetsManager();

	// Called before Assets Manager is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool Cleanup();

	SDL_RWops* LoadAsset(const char* path);
	size_t LoadXML(const char* path, char** buffer);

private:
	std::string m_PakFile;
public:
	bool use_pak;
private:

};

#endif // __ASSETSMANAGER_H__