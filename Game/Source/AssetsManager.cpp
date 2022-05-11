#include "AssetsManager.h"
#include "App.h"

#include "Defs.h"
#include "Log.h"

#include <string>

#include "External/PhysFS/include/physfsrwops.h"
#include "External/PhysFS/include/physfsrwops.c"

AssetsManager::AssetsManager(bool start_enabled) : Module(start_enabled)
{
	name.Create("assetsManager");
}

// Destructor
AssetsManager::~AssetsManager()
{
}

// Called before Assets Manager is available
bool AssetsManager::Awake(pugi::xml_node& config)
{
	LOG("Loading Assets Manager");
	bool ret = true;

	// (SOLVED) TODO 0: Initialize the PhysFS API and mount the Assets file, return false if there is any error

	use_pak = config.child("usepak").attribute("value").as_bool(false);

	m_PakFile = config.child("pakfile").text().as_string();

	if (PHYSFS_init(NULL) == 0)
	{
		LOG("ERROR IN PHYSFS INITIALIZATION: %s\n", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
		return false;
	}

	if (use_pak) {
		if (PHYSFS_mount(m_PakFile.c_str(), NULL, 1) == 0)
		{
			LOG("ERROR ADDING ARCHIVE TO SEARCH PATH: %s\n", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
			return false;
		}
	}

	return ret;
}

SDL_RWops* AssetsManager::LoadAsset(const char* path)
{
	if (!use_pak) return NULL;

	// (SOLVED) TODO 1: Check if the file (path) actually exists in the Assets ZIP

	if (PHYSFS_exists(path) == 0)
	{
		LOG("ERROR - FILE %s DOESNT EXIST IN THE SEARCH PATH: %s\n", path, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
		return NULL;
	}

	// (SOLVED) TODO 2: Open the file for reading using RWops structure by PhysFS, and return the result
	SDL_RWops* ret = PHYSFSRWOPS_openRead(path);

	if (ret == NULL)
	{
		LOG("ERROR OPENING FILE %s FOR READING: %s\n", path, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
		return NULL;
	}

	return ret;
}

size_t AssetsManager::LoadXML(const char* path, char** buffer)
{
	if (!use_pak) return NULL;

	// (SOLVED) TODO 3: Repeat what you have done in the LoadAsset() method but instead of using a RWops structure, use a PHYSFS_file
	if (PHYSFS_exists(path) == 0)
		LOG("ERROR - FILE %s DOESNT EXIST IN THE SEARCH PATH: %s\n", path, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));

	PHYSFS_file* file = PHYSFS_openRead(path);
	if (file == NULL)
		LOG("ERROR OPENING FILE %s FOR READING: %s\n", path, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));

	// (SOLVED) TODO 4: Check if PhysFS has not ended to read the file, obtain the size of the file in bytes
	if (!PHYSFS_eof(file))
	{
		PHYSFS_sint64 size = PHYSFS_fileLength(file);

		// (SOLVED) TODO 5: Allocate enough memory for the buffer to read the file
		*buffer = new char[size];

		PHYSFS_sint64 numBytesRead = PHYSFS_readBytes(file, *buffer, size);
		if (numBytesRead == -1)
			LOG("ERROR READING FROM FILEHANDLE: %s\n", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));

		// (SOLVED) TODO 6: Close the file when finished and return its number of bytes
		// If the reading process has finished it means that the number of bytes read is equal to the size of the file.
		if (numBytesRead == size)
		{
			if (PHYSFS_close(file) == 0)
				LOG("ERROR CLOSING FILEHANDLE: %s\n", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));

			return numBytesRead;
		}
		else
		{
			PHYSFS_close(file);
			RELEASE_ARRAY(buffer);
			return 0;
		}
	}
}

// Called before quitting
bool AssetsManager::Cleanup()
{
	LOG("Quitting Assets Manager");

	if (PHYSFS_deinit() == 0)
		LOG("ERROR DEINITIALIZING THE PHYSFS LIBRARY: %s\n", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));

	return true;
}