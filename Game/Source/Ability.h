#ifndef __ABILITY_H__
#define __ABILITY_H__

#include "Animation.h"
#include "Point.h"

class Character;
class SDL_Texture;

class Ability {
protected:
	Character* p_Character;

	Animation p_Animation;
	SDL_Texture* p_Texture;

	int p_FrameCount;
private:

public:
	Ability(Character* character);
	~Ability();

	void Update();
	void Render(iPoint position);

	virtual bool HasFinished() {
		return p_Animation.HasFinished();
	}

	void Reset() {
		p_FrameCount = 0;
		p_Animation.Reset();
	}

	virtual void Execute() = 0;
}; 

#endif  // __ABILITY_H__