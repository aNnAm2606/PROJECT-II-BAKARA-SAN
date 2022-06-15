#ifndef __FONTS_H__
#define __FONTS_H__

#include "Module.h"
#include "Log.h"
#include "Color.h"
#include "SDL\include\SDL_pixels.h"

#define MAX_FONTS 60
#define MAX_FONT_CHARS 256

struct SDL_Texture;

struct Font
{
	// Lookup table. All characters displayed in the same order as the texture
	char table[MAX_FONT_CHARS];

	// The font texture
	SDL_Texture* texture = nullptr;

	// Font setup data
	uint totalLength;
	uint rows, columns;
	uint char_w, char_h;
	Color color;
};

class Fonts : public Module
{
public:

	// Constructor
	Fonts(bool start_enabled);

	// Destructor
	~Fonts();

	// Loads a font file from a texture
	// Returns a font index from the fonts array
	// Param texturePath	- The path to the texture file
	// Param characters		- The lookup table. All characters displayed in the same order as the texture
	// Param rows			- The amount of character rows in the texture
	int Load(const char* texturePath, const char* characters, uint rows = 1, Color c = {255,255,255});

	// Removes a font by its index
	// Unloads the texture and removes it from the fonts array
	void UnLoad(int fontIndex);

	// Create a surface from text
	void BlitText(int x, int y, int fontIndex, const char* text, bool useCamera=true) const;

	Font& GetFont(int id) { return fonts[id]; }

private:
	// An array to keep track and store all loaded fonts
	Font fonts[MAX_FONTS];
};


#endif // __Fonts_H__

