#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Point.h"
#include "Animation.h"


class Particle
{

public:
	


	Particle();
	~Particle();
	bool Update(float dt);

	Point<int> position;
	Animation animation;

private:
	float timePassed = 0.0f;
	int lifeTime = 4;
};

#endif

