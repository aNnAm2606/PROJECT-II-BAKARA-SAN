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
	float timePassed;
	int lifeTime;
};

#endif

