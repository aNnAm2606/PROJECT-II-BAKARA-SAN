#ifndef __ABILITY_H__
#define __ABILITY_H__

#include "SDL/include/SDL.h"
#include "Animation.h"
#include "Point.h"

class Character;

class Ability {
protected:
	Character* p_Character;

	Animation p_Animation;
	SDL_Texture* p_Texture;

	int p_StartFrame;

	int p_FrameCount;
private:

public:
	Ability(Character* character);
	~Ability();

	int GetStartFrame() { return p_StartFrame; }

	void Update();
	virtual void Render(iPoint position) {}

	virtual bool HasFinished() {
		return p_Animation.HasFinished();
	}

	void Reset() {
		p_FrameCount = 0;
		p_Animation.Reset();
	}

	virtual void Execute(iPoint position) = 0;
}; 

#endif  // __ABILITY_H__